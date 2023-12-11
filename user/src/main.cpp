#include "main.h"

#include <map>
#include "../../simulator/include/emu_rtos.h"

void test_task_fn(void* _) {
    uint32_t time = 0;
    for(auto a : get_tasks()) {
        std::cout << a.first << std::endl;
    }
    while (true) {
        pros::c::task_delay_until(&time, 10);
        printf("Other: %d %d\n", time, pros::millis());
        fflush(stdout);
    }
}

void initialize() {
    pros::c::task_create(test_task_fn, nullptr, 0, 0, "Test");
    uint32_t time1 = 5;
    while (true) {
        pros::c::task_delay_until(&time1, 10);
        printf("Main: %d %d\n", time1, pros::millis());
        fflush(stdout);
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
