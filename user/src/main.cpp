#include "main.h"

#include <map>
#include "../../simulator/include/emu_rtos.h"

void test_task_fn(void* _) {
    uint32_t time = 0;
    for (auto a: get_tasks()) {
        std::cout << a.first << std::endl;
    }
    while (true) {
        pros::c::task_delay_until(&time, 10);
        time -= time % 5;
        printf("Other: %d %d\n", time, pros::millis());
        fflush(stdout);
    }
}

void initialize() {
    pros::task_t task = pros::c::task_create(test_task_fn, nullptr, 0, 0, "Test");
    uint32_t time = 5;
    while (true) {
        pros::c::task_delay_until(&time, 10);
        time -= time % 5;
        printf("Main: %d %d\n", time, pros::millis());
        fflush(stdout);
        if (time == 1005)
            pros::c::task_suspend(task);
        if (time == 2005)
            pros::c::task_resume(task);
        if(time == 3005)
            pros::c::task_delete(task);
        if(time == 4005)
            break;
    }
    for (auto a: get_tasks()) {
        std::cout << a.first << std::endl;
    }
}


void competition_initialize() {
}

void disabled() {
}

void autonomous() {
}

void opcontrol() {
}
