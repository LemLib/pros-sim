#include "emu_rtos.h"
#include "pros/rtos.hpp"
#include <map>

static std::vector<task_t_internal *> tasks;

bool task_exists(const char *name) {
    return std::any_of(tasks.begin(), tasks.end(), [name](task_t_internal *task) -> bool {
        return (strcmp(name, task->name) == 0);
    });
}


extern "C" pros::task_t task_get_by_name(const char *name) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [name](task_t_internal *task) -> bool {
        return (strcmp(name, task->name) == 0);
    });
    return it.base();
}

extern "C" void task_register(task_t_internal *task) {
    tasks.emplace_back(task);
}

extern "C" void task_deregister(task_t_internal *task) { (void) std::remove(tasks.begin(), tasks.end(), task); }

extern "C" uint32_t task_get_count() { return tasks.size(); }

extern "C" pros::task_t task_get_current() {
    const pthread_t current = pthread_self();
    for (const auto task: tasks) {
        if (pthread_equal(task->thread, current)) { return task; }
    }
    return nullptr;
}


namespace pros {
    using namespace pros::c;

    Task::Task(task_fn_t function, void *parameters, std::uint32_t prio, std::uint16_t stack_depth, const char *name) {
        task = task_create(function, parameters, prio, stack_depth, name);
    }

    Task::Task(task_fn_t function, void *parameters, const char *name)
            : Task(function, parameters, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, name) {}

    Task::Task(task_t task) : task(task) {}

    Task &Task::operator=(const task_t in) {
        task = in;
        return *this;
    }

    Task Task::current() {
        return Task{task_get_current()};
    }

    void Task::remove() {
        return task_delete(task);
    }

    std::uint32_t Task::get_priority() {
        return task_get_priority(task);
    }

    void Task::set_priority(std::uint32_t prio) {
        task_set_priority(task, prio);
    }

    std::uint32_t Task::get_state() {
        return task_get_state(task);
    }

    void Task::suspend() {
        task_suspend(task);
    }

    void Task::resume() {
        task_resume(task);
    }

    const char *Task::get_name() {
        return task_get_name(task);
    }

    std::uint32_t Task::notify() {
        return task_notify(task);
    }

    void Task::join() {
        return task_join(task);
    }

    std::uint32_t Task::notify_ext(std::uint32_t value, notify_action_e_t action, std::uint32_t *prev_value) {
        return task_notify_ext(task, value, action, prev_value);
    }

    std::uint32_t Task::notify_take(bool clear_on_exit, std::uint32_t timeout) {
        return task_notify_take(clear_on_exit, timeout);
    }

    bool Task::notify_clear() {
        return task_notify_clear(task);
    }

    void Task::delay(const std::uint32_t milliseconds) {
        task_delay(milliseconds);
    }

    void Task::delay_until(std::uint32_t *const prev_time, const std::uint32_t delta) {
        task_delay_until(prev_time, delta);
    }

    std::uint32_t Task::get_count() {
        return task_get_count();
    }

    Mutex::Mutex() : mutex(mutex_create(), mutex_delete) {}

    Clock::time_point Clock::now() {
        return time_point{duration{millis()}};
    }

    bool Mutex::take() {
        return mutex_take(mutex.get(), TIMEOUT_MAX);
    }

    bool Mutex::take(std::uint32_t timeout) {
        return mutex_take(mutex.get(), timeout);
    }

    bool Mutex::give() {
        return mutex_give(mutex.get());
    }

    void Mutex::lock() {
        if (!take(TIMEOUT_MAX)) {
            throw std::system_error(errno, std::system_category(), "Cannot obtain lock!");
        }
    }

    void Mutex::unlock() {
        give();
    }

    bool Mutex::try_lock() {
        return take(0);
    }
}  // namespace pros