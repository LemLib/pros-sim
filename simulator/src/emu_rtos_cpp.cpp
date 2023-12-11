#include "emu_rtos.h"
#include "pros/rtos.h"

#include <map>

std::map<const char*, task_t_internal*>& get_tasks() {
    static std::map<const char*, task_t_internal*> tasks;
    return tasks;
}

bool task_exists(const char* name) { return get_tasks().contains(name); }

pros::task_t task_get_by_name(const char* name) { return get_tasks()[name]; }

void task_register(task_t_internal* task) { get_tasks().emplace(task->name, task); }

void task_deregister(task_t_internal* task) { get_tasks().erase(task->name); }

uint32_t task_get_count() { return get_tasks().size(); }

pros::task_t task_get_current() {
    const pthread_t current = pthread_self();
    for (const auto map = get_tasks(); const auto [_, snd] : map) {
        if (pthread_equal(snd->pthread, current)) { return snd; }
    }
    return nullptr;
}

pros::Task::Task(task_fn_t function, void* parameters, std::uint32_t prio, std::uint16_t stack_depth,
                 const char* name) {
    task = c::task_create(function, parameters, prio, stack_depth, name);
}

pros::Task::Task(task_t task)
    : task(task) {}

pros::Task& pros::Task::operator=(task_t in) {

}
void pros::Task::remove() {
    return c::task_delete(task);
}

std::uint32_t pros::Task::get_priority() {
    return static_cast<task_t_internal*>(task)->prio;
}

void pros::Task::set_priority(std::uint32_t prio) {
    static_cast<task_t_internal*>(task)->prio = prio;

}
std::uint32_t pros::Task::get_state() {
    return c::task_get_state(task);
}
void pros::Task::suspend() {
    return c::task_suspend(task);
}
void pros::Task::resume() {
    return c::task_resume(task);
}
const char* pros::Task::get_name() {
    return static_cast<task_t_internal*>(task)->name;
}

std::uint32_t pros::Task::notify() {
    return c::task_notify(task);
}
void pros::Task::join() {
    return c::task_join(task);
}
std::uint32_t pros::Task::notify_ext(std::uint32_t value, notify_action_e_t action, std::uint32_t* prev_value) {
    return c::task_notify_ext(task, value, action, prev_value);
}

bool pros::Task::notify_clear() {
    return c::task_notify_clear(task);
}