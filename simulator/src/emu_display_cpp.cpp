#include "pros/screen.h"

#include <list>

#include "pros/apix.h"
#include "emu_devices.h"
#include "v5_api.h"

static std::list<pros::touch_event_cb_fn_t> touch_event_release_handler_list;
static std::list<pros::touch_event_cb_fn_t> touch_event_press_handler_list;
static std::list<pros::touch_event_cb_fn_t> touch_event_press_auto_handler_list;

pros::mutex_t screen_mutex = nullptr;

extern "C" uint32_t screen_touch_callback(pros::touch_event_cb_fn_t cb, pros::last_touch_e_t event_type) {
    if (!pros::c::mutex_take(screen_mutex, TIMEOUT_MAX)) {
        errno = EACCES;
        return PROS_ERR;
    }
    switch (event_type) {
        case pros::E_TOUCH_RELEASED:
            touch_event_release_handler_list.emplace_back(cb);
            break;
        case pros::E_TOUCH_PRESSED:
            touch_event_press_handler_list.emplace_back(cb);
            break;
        case pros::E_TOUCH_HELD:
            touch_event_press_auto_handler_list.emplace_back(cb);
            break;
        case pros::E_TOUCH_ERROR:
            return PROS_ERR;
    }
    if (!pros::c::mutex_give(screen_mutex)) {
        return PROS_ERR;
    } else {
        return 1;
    }
}


extern "C" inline bool _touch_status_equivalent(V5_TouchStatus x, V5_TouchStatus y) {
    return (x.lastEvent == y.lastEvent) && (x.lastXpos == y.lastXpos) && (x.lastYpos == y.lastYpos);
}

extern "C" [[noreturn]] void _touch_handle_task(void*) {
    V5_TouchStatus last, current;
    while (true) {
        pros::c::mutex_take(screen_mutex, TIMEOUT_MAX);
        vexTouchDataGet(&current);
        pros::c::mutex_give(screen_mutex);
        if (!_touch_status_equivalent(current, last)) {
            switch (current.lastEvent) {
                case kTouchEventRelease:
                    for(auto fun : touch_event_release_handler_list) {
                        if(fun)
                            fun();
                    }
                    break;
                case kTouchEventPress:
                    for(auto fun : touch_event_press_handler_list) {
                        if(fun)
                            fun();
                    }
                    break;
                case kTouchEventPressAuto:
                    for(auto fun : touch_event_press_auto_handler_list) {
                        if(fun)
                            fun();
                    }
                    break;
            }
            last = current;
        }
        pros::delay(10);
    }
}