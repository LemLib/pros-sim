#include "v5_api.h"
#include "SDL2/SDL.h"


SDL_GameController* findController() {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) { return SDL_GameControllerOpen(i); }
    }

    return NULL;
}

struct {
    SDL_GameController* controller;
    bool a: 1;
    bool b: 1;
    bool x: 1;
    bool y: 1;
    bool l: 1;
    bool r: 1;
    bool u: 1;
    bool d: 1;
    bool l1: 1;
    bool l2: 1;
    bool r1: 1;
    bool r2: 1;
    int8_t lx;
    int8_t rx;
    int8_t ly;
    int8_t ry;
} controller;

void handleControllerEvent(SDL_Event* e) {
    switch (e->type) {
        case SDL_CONTROLLERBUTTONUP:
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            break;
        case SDL_CONTROLLERAXISMOTION:
            int8_t value = e->caxis.value / -64;

            switch (e->caxis.axis) {
                case SDL_CONTROLLER_AXIS_LEFTY:

                    controller.ly = value;
                    printf("%d\n", value);
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTY:
                    controller.ry = value;
                    printf("%d\n", value);
                    break;
            }
            break;
        case SDL_CONTROLLERDEVICEADDED:
        case SDL_CONTROLLERDEVICEREMOVED:
            controller.controller = findController();
            break;
        default: break;
    }
}

// Controller
int32_t vexControllerGet(V5_ControllerId id, V5_ControllerIndex index) {
    switch (index) {
        case 1:
            return controller.ly;
        case 3:
            return controller.ry;
    }
    return 0;
}

V5_ControllerStatus vexControllerConnectionStatusGet(V5_ControllerId id) {
}

bool vexControllerTextSet(V5_ControllerId id, uint32_t line, uint32_t col, const char* str) {
}
