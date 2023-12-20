#include "emu_rtos.h"
#include <signal.h>

// literally just random magic numbers I pulled out
#define TASK_MAGIC 314159265
#define MUTEX_MAGIC 415926535

#define taskNOT_WAITING_NOTIFICATION ((uint8_t)0)
#define taskWAITING_NOTIFICATION ((uint8_t)1)
#define taskNOTIFICATION_RECEIVED ((uint8_t)2)

uint64_t get_start_time() {
    static int64_t start_time = -1;
    if (start_time == -1) {
        struct timespec tp = {};
        clock_gettime(CLOCK_MONOTONIC, &tp);
        start_time = tp.tv_sec * 1000000 + tp.tv_nsec / 1000;
    }
    return start_time;
}

void rtos_initialize() { (void)get_start_time(); }

uint32_t millis() {
    struct timespec tp = {};

    clock_gettime(CLOCK_MONOTONIC, &tp);
    return tp.tv_sec * 1000L + tp.tv_nsec / 1000000L - get_start_time() / 1000;
}

uint64_t micros() {
    struct timespec tp = {};

    clock_gettime(CLOCK_MONOTONIC, &tp);
    return tp.tv_sec * 1000000L + tp.tv_nsec / 1000L - get_start_time();
}

void* task_fn_wrapper(const void* parameters) {
    const task_fn_args* args = parameters;

    args->func(args->parameters);
    return 0;
}

void sig_func(const int sig) {
    const task_t_internal* current = task_get_current();
    if (!current) return;
    if (current->magic != TASK_MAGIC) return;
    switch (sig) {
        case SIGUSR1:
            signal(SIGUSR1, sig_func);
            pthread_mutex_lock((pthread_mutex_t*)&current->suspendMutex);
            *(bool*)&current->suspended = true; // todo this is awful but the linter doesn't like it otherwise
            pthread_cond_wait((pthread_cond_t*)&current->resumeCond, (pthread_mutex_t*)&current->suspendMutex);
            pthread_mutex_unlock((pthread_mutex_t*)&current->suspendMutex);
            break;
        case SIGUSR2:
            signal(SIGUSR2, sig_func);
            pthread_mutex_lock((pthread_mutex_t*)&current->suspendMutex);
            *(bool*)&current->suspended = false; // todo this is awful but the linter doesn't like it otherwise
            pthread_cond_signal((pthread_cond_t*)&current->resumeCond);
            pthread_mutex_unlock((pthread_mutex_t*)&current->suspendMutex);
            break;
        default: break;
    }
}

task_t task_create(task_fn_t function, void* const parameters, uint32_t prio, const uint16_t stack_depth,
                   const char* const name) {
    task_t_internal* task = malloc(sizeof(task_t_internal));
    task->prio = prio;
    task->stack_depth = stack_depth;
    task->args.func = function;
    task->args.parameters = parameters;
    task->name = name;
    task->suspended = false;
    task->deleted = false;
    task->magic = TASK_MAGIC;
    int result = pthread_attr_init(&task->pthread_attr);
    if (result) {
        free(task);
        errno = result;
        return NULL;
    }
    result = pthread_create(&task->thread, &task->pthread_attr, task_fn_wrapper, &task->args);
    if (result) {
        free(task);
        errno = result;
        return NULL;
    }
    task_register(task);
    signal(SIGUSR1, sig_func);
    signal(SIGUSR2, sig_func);
    return task;
}

void task_delete(task_t task) {
    if (!task) pthread_exit(0);
    task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC && !internal->deleted) {
        pthread_cancel(internal->thread);
        internal->deleted = true;
        task_deregister(task);
    }
}

void task_delay(const uint32_t milliseconds) { usleep(milliseconds * 1000); }

void delay(const uint32_t milliseconds) { usleep(milliseconds * 1000); }

void task_delay_until(uint32_t* const prev_time, const uint32_t delta) {
    const int32_t delay = *prev_time + delta - millis();
    if (delay < 1) return;
    task_delay(delay);
    *prev_time = millis();
}

uint32_t task_get_priority(task_t task) {
    if (!task) return -1;
    const task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC && !internal->deleted) { return internal->prio; }
    return -1;
}

void task_set_priority(task_t task, uint32_t prio) {
    if (!task) return;
    task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC && !internal->deleted) { internal->prio = prio; }
}

task_state_e_t task_get_state(task_t task) {
    if (!task) return E_TASK_STATE_INVALID;
    const task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC) {
        if (internal->deleted) return E_TASK_STATE_DELETED;
        if (internal->suspended) return E_TASK_STATE_SUSPENDED;
        return E_TASK_STATE_RUNNING;
    }
    return E_TASK_STATE_INVALID;
}

void task_suspend(task_t task) {
    if (!task) return;
    const task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC && !internal->deleted) pthread_kill(internal->thread, SIGUSR1);
}

void task_resume(task_t task) {
    if (!task) return;
    const task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC && !internal->deleted) pthread_kill(internal->thread, SIGUSR2);
}

char* task_get_name(task_t task) {
    if (!task) return NULL;
    const task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC && !internal->deleted) { return (char*)internal->name; }
    return NULL;
}

uint32_t task_notify(task_t task) { return task_notify_ext(task, 0, E_NOTIFY_ACTION_INCR, NULL); }

void task_join(task_t task) {
    if (!task) return;
    const task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC && !internal->deleted) { pthread_join(internal->thread, NULL); }
}

uint32_t task_notify_ext(task_t task, uint32_t value, notify_action_e_t action, uint32_t* prev_value) {
    if (!task) return 0;
    int32_t xReturn = 0;
    task_t_internal* internal = task;
    if (internal->magic != TASK_MAGIC || internal->deleted) return 0;
    uint8_t ucOriginalNotifyState = internal->ucNotifyState;
    internal->ucNotifyState = taskNOTIFICATION_RECEIVED;
    switch (action) {
        case E_NOTIFY_ACTION_BITS: internal->ulNotifiedValue |= value; break;

        case E_NOTIFY_ACTION_INCR: internal->ulNotifiedValue++; break;

        case E_NOTIFY_ACTION_OWRITE: internal->ulNotifiedValue = value; break;

        case E_NOTIFY_ACTION_NO_OWRITE:
            if (ucOriginalNotifyState != taskNOTIFICATION_RECEIVED) {
                internal->ulNotifiedValue = value;
            } else {
                /* The value could not be written to the task. */
                xReturn = 1;
            }
            break;

        case E_NOTIFY_ACTION_NONE:
            /* The task is being notified without its notify value being
            updated. */
            break;
    }
    return xReturn;
}

uint32_t task_notify_take(bool clear_on_exit, uint32_t timeout) {
    
}

bool task_notify_clear(task_t task) {}

mutex_t mutex_create() {
    mutex_t_internal* mutex = malloc(sizeof(mutex_t_internal));
    int result = pthread_mutexattr_init(&mutex->attr);
    if (result) {
        errno = result;
        free(mutex);
        return NULL;
    }
    result = pthread_mutex_init(&mutex->mutex, &mutex->attr);
    if (result) {
        errno = result;
        free(mutex);
        return NULL;
    }
    mutex->deleted = false;
    mutex->magic = MUTEX_MAGIC;
    return mutex;
}

bool mutex_take(mutex_t mutex, uint32_t timeout) {
    mutex_t_internal* internal = mutex;
    if (internal->magic != MUTEX_MAGIC || internal->deleted) return false;
    struct timespec tp = {};

    clock_gettime(CLOCK_REALTIME, &tp);
    tp.tv_sec += timeout / 1000;
    tp.tv_nsec += timeout % 1000 * 1000000;
    if (tp.tv_nsec > 1000000000) {
        tp.tv_nsec -= 1000000000;
        tp.tv_sec++;
    }
    const int result = pthread_mutex_timedlock(&internal->mutex, &tp);
    if (!result) return true;
    errno = result;
    return false;
}

bool mutex_give(mutex_t mutex) {
    mutex_t_internal* internal = mutex;
    if (internal->magic != MUTEX_MAGIC || internal->deleted) return false;
    const int result = pthread_mutex_unlock(&internal->mutex);
    if (!result) return true;
    errno = result;
    return false;
}

void mutex_delete(mutex_t mutex) {
    mutex_t_internal* internal = mutex;
    if (internal->magic != MUTEX_MAGIC || internal->deleted) return;
    internal->deleted = true;
    pthread_mutex_destroy(&internal->mutex);
    pthread_mutexattr_destroy(&internal->attr);
}

mutex_t mutex_create_static(sem_t* mutex_buffer) {}
