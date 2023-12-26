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

static int8_t JoystickValue( int16_t value )
{
    return (int8_t) ((float) value * ( ( value >= 0 ) ? ( 127.0f / 32767.0f ) : ( 127.0f / 32768.0f ) ));
}


void controllerUpdate() {
    if(controller.controller == NULL) return;
    controller.lx = (int8_t) JoystickValue(SDL_GameControllerGetAxis(controller.controller, SDL_CONTROLLER_AXIS_LEFTX));
    controller.ly = (int8_t) -JoystickValue(SDL_GameControllerGetAxis(controller.controller, SDL_CONTROLLER_AXIS_LEFTY));
    controller.rx = (int8_t) JoystickValue(SDL_GameControllerGetAxis(controller.controller, SDL_CONTROLLER_AXIS_RIGHTX));
    controller.ry = (int8_t) -JoystickValue(SDL_GameControllerGetAxis(controller.controller, SDL_CONTROLLER_AXIS_RIGHTY));
    //printf("%d %d %d %d\n", controller.lx, controller.ly, controller.rx, controller.ry);
}
void handleControllerEvent(SDL_Event* e) {
    switch (e->type) {
        case SDL_CONTROLLERDEVICEADDED:
            SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
        case SDL_CONTROLLERDEVICEREMOVED:
            controller.controller = findController();
            break;
        default: break;
    }
}

// Controller
int32_t vexControllerGet(V5_ControllerId id, V5_ControllerIndex index) {
    switch (index) {
        case AnaLeftY:
            return controller.ly;
        case AnaRightY:
            return controller.ry;
        case AnaLeftX:
            return controller.lx;
        case AnaRightX:
            return controller.rx;
        case AnaSpare1:
            break;
        case AnaSpare2:
            break;
        case Button5U:
            break;
        case Button5D:
            break;
        case Button6U:
            break;
        case Button6D:
            break;
        case Button7U:
            break;
        case Button7D:
            break;
        case Button7L:
            break;
        case Button7R:
            break;
        case Button8U:
            break;
        case Button8D:
            break;
        case Button8L:
            break;
        case Button8R:
            break;
        case ButtonSEL:
            break;
        case BatteryLevel:
            break;
        case ButtonAll:
            break;
        case Flags:
            break;
        case BatteryCapacity:
            break;
    }
    return 0;
}

V5_ControllerStatus vexControllerConnectionStatusGet(V5_ControllerId id) {
}

bool vexControllerTextSet(V5_ControllerId id, uint32_t line, uint32_t col, const char* str) {
}
