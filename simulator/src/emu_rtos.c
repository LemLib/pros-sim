#include "emu_rtos.h"

#include <signal.h>

#define TASK_MAGIC 314159265

uint64_t get_start_time() {
    static int64_t start_time = -1;
    if (start_time == -1) {
        struct timespec tp;
        clock_gettime(CLOCK_MONOTONIC, &tp);
        start_time = tp.tv_sec * 1000000 + tp.tv_nsec / 1000;
    }
    return start_time;
}

void rtos_initialize() {
    (void) get_start_time();
}

uint32_t millis(void) {
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);
    return tp.tv_sec * 1000L + tp.tv_nsec / 1000000L - get_start_time() / 1000;
}

uint64_t micros(void) {
    struct timespec tp;

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
            pthread_mutex_lock((pthread_mutex_t *) &current->suspendMutex);
            *(bool *) &current->suspended = true; //todo this is awful but the linter doesn't like it otherwise
            pthread_cond_wait((pthread_cond_t *) &current->resumeCond,
                              (pthread_mutex_t *) &current->suspendMutex);
            pthread_mutex_unlock((pthread_mutex_t *) &current->suspendMutex);
            break;
        case SIGUSR2:
            signal(SIGUSR2, sig_func);
            pthread_mutex_lock((pthread_mutex_t *) &current->suspendMutex);
            *(bool *) &current->suspended = false; //todo this is awful but the linter doesn't like it otherwise
            pthread_cond_signal((pthread_cond_t *) &current->resumeCond);
            pthread_mutex_unlock((pthread_mutex_t *) &current->suspendMutex);
            break;
        default:
            break;
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
    if (pthread_create(&task->thread, &task->pthread_attr, task_fn_wrapper, &task->args)) {
        free(task);
        errno = ENOMEM;
        return 0;
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
    int32_t delay = *prev_time + delta - millis();
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
    if (internal->magic == TASK_MAGIC)
        pthread_kill(internal->thread, SIGUSR1);
}

void task_resume(task_t task) {
    if (!task) return;
    const task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC)
        pthread_kill(internal->thread, SIGUSR2);
}

char* task_get_name(task_t task) {
    if (!task) return NULL;
    const task_t_internal* internal = task;
    if (internal->magic == TASK_MAGIC && !internal->deleted) { return (char *) internal->name; }
    return NULL;
}

uint32_t task_notify(task_t task) {
}

void task_join(task_t task) {
}

uint32_t task_notify_ext(task_t task, uint32_t value, notify_action_e_t action, uint32_t* prev_value) {
}

uint32_t task_notify_take(bool clear_on_exit, uint32_t timeout) {
}

bool task_notify_clear(task_t task) {
}

mutex_t mutex_create(void) {
}

bool mutex_take(mutex_t mutex, uint32_t timeout) {
}

bool mutex_give(mutex_t mutex) {
}

void mutex_delete(mutex_t mutex) {
}

mutex_t mutex_create_static(sem_t* mutex_buffer) {
}
