#include "v5_api.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include "stdio.h"

#include <emu_devices.h>

struct {
        SDL_Renderer* renderer;
        SDL_Window* window;
        bool init;

        union {
                uint32_t foreground_color;

                struct __attribute((packed)) {
                        uint8_t fg_b;
                        uint8_t fg_g;
                        uint8_t fg_r;
                        uint8_t fg_a;
                };
        };

        union {
                uint32_t background_color;

                struct __attribute((packed)) {
                        uint8_t bg_b;
                        uint8_t bg_g;
                        uint8_t bg_r;
                        uint8_t bg_a;
                };
        };
} display;

struct {
        V5_TouchEvent last;
        uint16_t x, y;
} touch;

bool sim_SDL_init() {
    display.init = false;
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    display.window = SDL_CreateWindow("Brain screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      SYSTEM_DISPLAY_WIDTH, SYSTEM_DISPLAY_HEIGHT, windowFlags);

    if (!display.window) {
        printf("Failed to open %d x %d window: %s\n", SYSTEM_DISPLAY_WIDTH, SYSTEM_DISPLAY_HEIGHT, SDL_GetError());
        return false;
    }

    display.renderer = SDL_CreateRenderer(display.window, -1, rendererFlags);

    if (!display.renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(display.window);
        return false;
    }

    display.init = true;
    return true;
}

void handleControllerEvent(SDL_Event* e);

void display_background_processing() {
    bool buttonDown = false;
    static SDL_Event e;
    static int a = 0;
    a++;
    if (a % 10 != 0) return;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                    printf("Window closed!\n");
                    vexSystemExitRequest();
                }
                break;
            case SDL_QUIT:
                printf("Window closed!\n");
                vexSystemExitRequest();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.windowID == SDL_GetWindowID(display.window)) {
                    touch.x = e.button.x;
                    touch.y = e.button.y;
                    buttonDown = true;
                    touch.last = kTouchEventPress;
                }
                break;
            case SDL_MOUSEMOTION:
                if (e.button.windowID == SDL_GetWindowID(display.window) &&
                    (touch.last == kTouchEventPress || touch.last == kTouchEventPressAuto) && !buttonDown) {
                    touch.x = e.button.x;
                    touch.y = e.button.y;
                    touch.last = kTouchEventPressAuto;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.windowID == SDL_GetWindowID(display.window)) {
                    touch.x = e.button.x;
                    touch.y = e.button.y;
                    touch.last = kTouchEventRelease;
                }
                break;
            case SDL_CONTROLLERDEVICEADDED:
            case SDL_CONTROLLERDEVICEREMOVED:
                handleControllerEvent(&e);
                break;
            default: break;
        }
    }
    SDL_RenderPresent(display.renderer);
}

// Display/graphics
void vexDisplayForegroundColor(uint32_t col) { display.foreground_color = col; }

void vexDisplayBackgroundColor(uint32_t col) { display.background_color = col; }

uint32_t vexDisplayForegroundColorGet() { return display.foreground_color; }

uint32_t vexDisplayBackgroundColorGet() { return display.background_color; }

void vexDisplayErase() {
    SDL_SetRenderDrawColor(display.renderer, display.bg_r, display.bg_g, display.bg_b, 255 - display.bg_a);
    SDL_RenderClear(display.renderer);
    SDL_SetRenderDrawBlendMode(display.renderer, SDL_BLENDMODE_NONE); // todo: check if this is right
}

void vexDisplayScroll(int32_t nStartLine, int32_t nLines) {}

void vexDisplayScrollRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t nLines) {}

void vexDisplayCopyRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t* pSrc, int32_t srcStride) {}

void vexDisplayPixelSet(uint32_t x, uint32_t y) {
    pixelRGBA(display.renderer, x, y, display.fg_r, display.fg_g, display.fg_b, 255 - display.fg_a);
}

void vexDisplayPixelClear(uint32_t x, uint32_t y) {
    pixelRGBA(display.renderer, x, y, display.bg_r, display.bg_g, display.bg_b, 255 - display.bg_a);
}

void vexDisplayLineDraw(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    lineRGBA(display.renderer, x1, y1, x2, y2, display.fg_r, display.fg_g, display.fg_b, 255 - display.fg_a);
}

void vexDisplayLineClear(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    lineRGBA(display.renderer, x1, y1, x2, y2, display.bg_r, display.bg_g, display.bg_b, 255 - display.bg_a);
}

void vexDisplayRectDraw(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    rectangleRGBA(display.renderer, x1, y1, x2, y2, display.fg_r, display.fg_g, display.fg_b, 255 - display.fg_a);
}

void vexDisplayRectClear(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    boxRGBA(display.renderer, x1, y1, x2, y2, display.bg_r, display.bg_g, display.bg_b, 255 - display.bg_a);
}

void vexDisplayRectFill(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    boxRGBA(display.renderer, x1, y1, x2, y2, display.fg_r, display.fg_g, display.fg_b, 255 - display.fg_a);
}

void vexDisplayCircleDraw(int32_t xc, int32_t yc, int32_t radius) {
    circleRGBA(display.renderer, xc, yc, radius, display.fg_r, display.fg_g, display.fg_b, 255 - display.fg_a);
}

void vexDisplayCircleClear(int32_t xc, int32_t yc, int32_t radius) {
    filledCircleRGBA(display.renderer, xc, yc, radius, display.bg_r, display.bg_g, display.bg_b, 255 - display.bg_a);
}

void vexDisplayCircleFill(int32_t xc, int32_t yc, int32_t radius) {
    filledCircleRGBA(display.renderer, xc, yc, radius, display.fg_r, display.fg_g, display.fg_b, 255 - display.fg_a);
}

void vexDisplayPrintf(int32_t xpos, int32_t ypos, uint32_t bOpaque, const char* format, ...) {}

void vexDisplayString(const int32_t nLineNumber, const char* format, ...) {}

void vexDisplayStringAt(int32_t xpos, int32_t ypos, const char* format, ...) {}

void vexDisplayBigString(const int32_t nLineNumber, const char* format, ...) {}

void vexDisplayBigStringAt(int32_t xpos, int32_t ypos, const char* format, ...) {}

void vexDisplaySmallStringAt(int32_t xpos, int32_t ypos, const char* format, ...) {}

void vexDisplayCenteredString(const int32_t nLineNumber, const char* format, ...) {}

void vexDisplayBigCenteredString(const int32_t nLineNumber, const char* format, ...) {}

// Not really for user code but we need these for some wrapper functions
void vexDisplayVPrintf(int32_t xpos, int32_t ypos, uint32_t bOpaque, const char* format, va_list args) {}

void vexDisplayVString(const int32_t nLineNumber, const char* format, va_list args) {}

void vexDisplayVStringAt(int32_t xpos, int32_t ypos, const char* format, va_list args) {}

void vexDisplayVBigString(const int32_t nLineNumber, const char* format, va_list args) {}

void vexDisplayVBigStringAt(int32_t xpos, int32_t ypos, const char* format, va_list args) {}

void vexDisplayVSmallStringAt(int32_t xpos, int32_t ypos, const char* format, va_list args) {}

void vexDisplayVCenteredString(const int32_t nLineNumber, const char* format, va_list args) {}

void vexDisplayVBigCenteredString(const int32_t nLineNumber, const char* format, va_list args) {}

void vexDisplayTextSize(uint32_t n, uint32_t d) {}

void vexDisplayFontNamedSet(const char* pFontName) {}

int32_t vexDisplayStringWidthGet(const char* pString) {}

int32_t vexDisplayStringHeightGet(const char* pString) {}

bool vexDisplayRender(bool bVsyncWait, bool bRunScheduler) {}

void vexDisplayDoubleBufferDisable() {}

void vexDisplayClipRegionSet(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {}

void vexDisplayClipRegionClear() {}

uint32_t vexImageBmpRead(const uint8_t* ibuf, v5_image* oBuf, uint32_t maxw, uint32_t maxh) {}

uint32_t vexImagePngRead(const uint8_t* ibuf, v5_image* oBuf, uint32_t maxw, uint32_t maxh, uint32_t ibuflen) {}

void vexTouchUserCallbackSet(void (*callback)(V5_TouchEvent, int32_t, int32_t)) {}

bool vexTouchDataGet(V5_TouchStatus* status) {
    status->lastEvent = touch.last;
    status->lastXpos = touch.x;
    status->lastYpos = touch.y;
    return touch.last != kTouchEventRelease;
}
