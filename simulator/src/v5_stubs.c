#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "v5_api.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

void vexBackgroundProcessing(void) {}

// Console output
int32_t vexDebug(char const *fmt, ...) { return 0; }

int32_t vex_printf(char const *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    return vprintf(fmt, va);
    va_end(va);
}

int32_t vex_sprintf(char *out, const char *format, ...) {
    va_list va;
    va_start(va, format);
    return vsprintf(out, format, va);
    va_end(va);
}

int32_t vex_snprintf(char *out, uint32_t max_len, const char *format, ...) {
    va_list va;
    va_start(va, format);
    return vsnprintf(out, max_len, format, va);
    va_end(va);
}

int32_t vex_vsprintf(char *out, const char *format, va_list args) {
    return vsprintf(out, format, args);
}

int32_t vex_vsnprintf(char *out, uint32_t max_len, const char *format, va_list args) {
    return vsnprintf(out, max_len, format, args);
}

// system
uint32_t vexSystemTimeGet(void) {}

void vexGettime(struct time *pTime) {}

void vexGetdate(struct date *pDate) {}

void vexSystemMemoryDump(void) {}

void vexSystemDigitalIO(uint32_t pin, uint32_t value) {}

uint32_t vexSystemStartupOptions(void) {}

__attribute((noreturn)) void vexSystemExitRequest(void) {
    puts("Shutting down!\n");
    exit(0);
}

uint64_t vexSystemHighResTimeGet(void) {

}

uint64_t vexSystemPowerupTimeGet(void) {}

uint32_t vexSystemLinkAddrGet(void) {}

uint32_t vexSystemUsbStatus(void) {}

uint32_t vexDeviceButtonStateGet(void) {}

// Controller
int32_t vexControllerGet(V5_ControllerId id, V5_ControllerIndex index) {}

V5_ControllerStatus vexControllerConnectionStatusGet(V5_ControllerId id) {}

bool vexControllerTextSet(V5_ControllerId id, uint32_t line, uint32_t col, const char *str) {}

// LED sensor
void vexDeviceLedSet(V5_DeviceT device, V5_DeviceLedColor value) {}

void vexDeviceLedRgbSet(V5_DeviceT device, uint32_t color) {}

V5_DeviceLedColor vexDeviceLedGet(V5_DeviceT device) {}

uint32_t vexDeviceLedRgbGet(V5_DeviceT device) {}

// ADI sensor
void vexDeviceAdiPortConfigSet(V5_DeviceT device, uint32_t port, V5_AdiPortConfiguration type) {}

V5_AdiPortConfiguration vexDeviceAdiPortConfigGet(V5_DeviceT device, uint32_t port) {}

void vexDeviceAdiValueSet(V5_DeviceT device, uint32_t port, int32_t value) {}

int32_t vexDeviceAdiValueGet(V5_DeviceT device, uint32_t port) {}

// Bumper switch
V5_DeviceBumperState vexDeviceBumperGet(V5_DeviceT device) {}

// Gyro - obsolete, there is currently no dedicated gyro
void vexDeviceGyroReset(V5_DeviceT device) {}

double vexDeviceGyroHeadingGet(V5_DeviceT device) {}

double vexDeviceGyroDegreesGet(V5_DeviceT device) {}

// Sonar - obsolete, there is currently no dedicated gyro
int32_t vexDeviceSonarValueGet(V5_DeviceT device) {}

// Generic sensor - (who knows !)
int32_t vexDeviceGenericValueGet(V5_DeviceT device) {}

// Vision sensor
void vexDeviceVisionModeSet(V5_DeviceT device, V5VisionMode mode) {}

V5VisionMode vexDeviceVisionModeGet(V5_DeviceT device) {}

int32_t vexDeviceVisionObjectCountGet(V5_DeviceT device) {}

int32_t vexDeviceVisionObjectGet(V5_DeviceT device, uint32_t indexObj, V5_DeviceVisionObject *pObject) {}

void vexDeviceVisionSignatureSet(V5_DeviceT device, V5_DeviceVisionSignature *pSignature) {}

bool vexDeviceVisionSignatureGet(V5_DeviceT device, uint32_t id, V5_DeviceVisionSignature *pSignature) {}

void vexDeviceVisionBrightnessSet(V5_DeviceT device, uint8_t percent) {}

uint8_t vexDeviceVisionBrightnessGet(V5_DeviceT device) {}

void vexDeviceVisionWhiteBalanceModeSet(V5_DeviceT device, V5VisionWBMode mode) {}

V5VisionWBMode vexDeviceVisionWhiteBalanceModeGet(V5_DeviceT device) {}

void vexDeviceVisionWhiteBalanceSet(V5_DeviceT device, V5_DeviceVisionRgb color) {}

V5_DeviceVisionRgb vexDeviceVisionWhiteBalanceGet(V5_DeviceT device) {}

void vexDeviceVisionLedModeSet(V5_DeviceT device, V5VisionLedMode mode) {}

V5VisionLedMode vexDeviceVisionLedModeGet(V5_DeviceT device) {}

void vexDeviceVisionLedBrigntnessSet(V5_DeviceT device, uint8_t percent) {}

uint8_t vexDeviceVisionLedBrigntnessGet(V5_DeviceT device) {}

void vexDeviceVisionLedColorSet(V5_DeviceT device, V5_DeviceVisionRgb color) {}

V5_DeviceVisionRgb vexDeviceVisionLedColorGet(V5_DeviceT device) {}

void vexDeviceVisionWifiModeSet(V5_DeviceT device, V5VisionWifiMode mode) {}

V5VisionWifiMode vexDeviceVisionWifiModeGet(V5_DeviceT device) {}

// IMU
void vexDeviceImuReset(V5_DeviceT device) {}

double vexDeviceImuHeadingGet(V5_DeviceT device) {}

double vexDeviceImuDegreesGet(V5_DeviceT device) {}

void vexDeviceImuQuaternionGet(V5_DeviceT device, V5_DeviceImuQuaternion *data) {}

void vexDeviceImuAttitudeGet(V5_DeviceT device, V5_DeviceImuAttitude *data) {}

void vexDeviceImuRawGyroGet(V5_DeviceT device, V5_DeviceImuRaw *data) {}

void vexDeviceImuRawAccelGet(V5_DeviceT device, V5_DeviceImuRaw *data) {}

uint32_t vexDeviceImuStatusGet(V5_DeviceT device) {}

void vexDeviceImuModeSet(V5_DeviceT device, uint32_t mode) {}

uint32_t vexDeviceImuModeGet(V5_DeviceT device) {}

void vexDeviceImuDataRateSet(V5_DeviceT device, uint32_t rate) {}

// Rangefinder/Lidar - actual API to be determined
int32_t vexDeviceRangeValueGet(V5_DeviceT device) {}

// Absolute encoder
void vexDeviceAbsEncReset(V5_DeviceT device) {}

void vexDeviceAbsEncPositionSet(V5_DeviceT device, int32_t position) {}

int32_t vexDeviceAbsEncPositionGet(V5_DeviceT device) {}

int32_t vexDeviceAbsEncVelocityGet(V5_DeviceT device) {}

int32_t vexDeviceAbsEncAngleGet(V5_DeviceT device) {}

void vexDeviceAbsEncReverseFlagSet(V5_DeviceT device, bool value) {}

bool vexDeviceAbsEncReverseFlagGet(V5_DeviceT device) {}

uint32_t vexDeviceAbsEncStatusGet(V5_DeviceT device) {}

void vexDeviceAbsEncDataRateSet(V5_DeviceT device, uint32_t rate) {}

// Optical/color sensor
double vexDeviceOpticalHueGet(V5_DeviceT device) {}

double vexDeviceOpticalSatGet(V5_DeviceT device) {}

double vexDeviceOpticalBrightnessGet(V5_DeviceT device) {}

int32_t vexDeviceOpticalProximityGet(V5_DeviceT device) {}

void vexDeviceOpticalRgbGet(V5_DeviceT device, V5_DeviceOpticalRgb *data) {}

void vexDeviceOpticalLedPwmSet(V5_DeviceT device, int32_t value) {}

int32_t vexDeviceOpticalLedPwmGet(V5_DeviceT device) {}

uint32_t vexDeviceOpticalStatusGet(V5_DeviceT device) {}

void vexDeviceOpticalRawGet(V5_DeviceT device, V5_DeviceOpticalRaw *data) {}

void vexDeviceOpticalModeSet(V5_DeviceT device, uint32_t mode) {}

uint32_t vexDeviceOpticalModeGet(V5_DeviceT device) {}

uint32_t vexDeviceOpticalGestureGet(V5_DeviceT, V5_DeviceOpticalGesture *pData) {}

void vexDeviceOpticalGestureEnable(V5_DeviceT) {}

void vexDeviceOpticalGestureDisable(V5_DeviceT) {}

int32_t vexDeviceOpticalProximityThreshold(V5_DeviceT device, int32_t value) {}

void vexDeviceOpticalIntegrationTimeSet(V5_DeviceT device, double timeMs) {}

double vexDeviceOpticalIntegrationTimeGet(V5_DeviceT device) {}

// Electro magnet
void vexDeviceMagnetPowerSet(V5_DeviceT device, int32_t value, int32_t time) {}

int32_t vexDeviceMagnetPowerGet(V5_DeviceT device) {}

void vexDeviceMagnetPickup(V5_DeviceT device, V5_DeviceMagnetDuration duration) {}

void vexDeviceMagnetDrop(V5_DeviceT device, V5_DeviceMagnetDuration duration) {}

double vexDeviceMagnetTemperatureGet(V5_DeviceT device) {}

double vexDeviceMagnetCurrentGet(V5_DeviceT device) {}

uint32_t vexDeviceMagnetStatusGet(V5_DeviceT device) {}

// Distance
uint32_t vexDeviceDistanceDistanceGet(V5_DeviceT device) {}

uint32_t vexDeviceDistanceConfidenceGet(V5_DeviceT device) {}

int32_t vexDeviceDistanceObjectSizeGet(V5_DeviceT device) {}

double vexDeviceDistanceObjectVelocityGet(V5_DeviceT device) {}

uint32_t vexDeviceDistanceStatusGet(V5_DeviceT device) {}

// Gps
void vexDeviceGpsReset(V5_DeviceT device) {}

double vexDeviceGpsHeadingGet(V5_DeviceT device) {}

double vexDeviceGpsDegreesGet(V5_DeviceT device) {}

void vexDeviceGpsQuaternionGet(V5_DeviceT device, V5_DeviceGpsQuaternion *data) {}

void vexDeviceGpsAttitudeGet(V5_DeviceT device, V5_DeviceGpsAttitude *data, bool bRaw) {}

void vexDeviceGpsRawGyroGet(V5_DeviceT device, V5_DeviceGpsRaw *data) {}

void vexDeviceGpsRawAccelGet(V5_DeviceT device, V5_DeviceGpsRaw *data) {}

uint32_t vexDeviceGpsStatusGet(V5_DeviceT device) {}

void vexDeviceGpsModeSet(V5_DeviceT device, uint32_t mode) {}

uint32_t vexDeviceGpsModeGet(V5_DeviceT device) {}

void vexDeviceGpsDataRateSet(V5_DeviceT device, uint32_t rate) {}

void vexDeviceGpsOriginSet(V5_DeviceT device, double ox, double oy) {}

void vexDeviceGpsOriginGet(V5_DeviceT device, double *ox, double *oy) {}

void vexDeviceGpsRotationSet(V5_DeviceT device, double value) {}

double vexDeviceGpsRotationGet(V5_DeviceT device) {}

void vexDeviceGpsInitialPositionSet(V5_DeviceT device, double initial_x, double initial_y, double initial_rotation) {}

double vexDeviceGpsErrorGet(V5_DeviceT device) {}

// Generic serial port comms to any device
void vexDeviceGenericSerialEnable(V5_DeviceT device, int32_t options) {}

void vexDeviceGenericSerialBaudrate(V5_DeviceT device, int32_t baudrate) {}

int32_t vexDeviceGenericSerialWriteChar(V5_DeviceT device, uint8_t c) {}

int32_t vexDeviceGenericSerialWriteFree(V5_DeviceT device) {}

int32_t vexDeviceGenericSerialTransmit(V5_DeviceT device, uint8_t *buffer, int32_t length) {}

int32_t vexDeviceGenericSerialReadChar(V5_DeviceT device) {}

int32_t vexDeviceGenericSerialPeekChar(V5_DeviceT device) {}

int32_t vexDeviceGenericSerialReceiveAvail(V5_DeviceT device) {}

int32_t vexDeviceGenericSerialReceive(V5_DeviceT device, uint8_t *buffer, int32_t length) {}

void vexDeviceGenericSerialFlush(V5_DeviceT device) {}

// Display/graphics
void vexDisplayForegroundColor(uint32_t col) {}

void vexDisplayBackgroundColor(uint32_t col) {}

uint32_t vexDisplayForegroundColorGet(void) {}

uint32_t vexDisplayBackgroundColorGet(void) {}

void vexDisplayErase(void) {}

void vexDisplayScroll(int32_t nStartLine, int32_t nLines) {}

void vexDisplayScrollRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t nLines) {}

void vexDisplayCopyRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t *pSrc, int32_t srcStride) {}

void vexDisplayPixelSet(uint32_t x, uint32_t y) {}

void vexDisplayPixelClear(uint32_t x, uint32_t y) {}

void vexDisplayLineDraw(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {}

void vexDisplayLineClear(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {}

void vexDisplayRectDraw(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {}

void vexDisplayRectClear(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {}

void vexDisplayRectFill(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {}

void vexDisplayCircleDraw(int32_t xc, int32_t yc, int32_t radius) {}

void vexDisplayCircleClear(int32_t xc, int32_t yc, int32_t radius) {}

void vexDisplayCircleFill(int32_t xc, int32_t yc, int32_t radius) {}

void vexDisplayPrintf(int32_t xpos, int32_t ypos, uint32_t bOpaque, const char *format, ...) {}

void vexDisplayString(const int32_t nLineNumber, const char *format, ...) {}

void vexDisplayStringAt(int32_t xpos, int32_t ypos, const char *format, ...) {}

void vexDisplayBigString(const int32_t nLineNumber, const char *format, ...) {}

void vexDisplayBigStringAt(int32_t xpos, int32_t ypos, const char *format, ...) {}

void vexDisplaySmallStringAt(int32_t xpos, int32_t ypos, const char *format, ...) {}

void vexDisplayCenteredString(const int32_t nLineNumber, const char *format, ...) {}

void vexDisplayBigCenteredString(const int32_t nLineNumber, const char *format, ...) {}

// Not really for user code but we need these for some wrapper functions
void vexDisplayVPrintf(int32_t xpos, int32_t ypos, uint32_t bOpaque, const char *format, va_list args) {}

void vexDisplayVString(const int32_t nLineNumber, const char *format, va_list args) {}

void vexDisplayVStringAt(int32_t xpos, int32_t ypos, const char *format, va_list args) {}

void vexDisplayVBigString(const int32_t nLineNumber, const char *format, va_list args) {}

void vexDisplayVBigStringAt(int32_t xpos, int32_t ypos, const char *format, va_list args) {}

void vexDisplayVSmallStringAt(int32_t xpos, int32_t ypos, const char *format, va_list args) {}

void vexDisplayVCenteredString(const int32_t nLineNumber, const char *format, va_list args) {}

void vexDisplayVBigCenteredString(const int32_t nLineNumber, const char *format, va_list args) {}

void vexDisplayTextSize(uint32_t n, uint32_t d) {}

void vexDisplayFontNamedSet(const char *pFontName) {}

int32_t vexDisplayStringWidthGet(const char *pString) {}

int32_t vexDisplayStringHeightGet(const char *pString) {}

bool vexDisplayRender(bool bVsyncWait, bool bRunScheduler) {}

void vexDisplayDoubleBufferDisable(void) {}

void vexDisplayClipRegionSet(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {}

void vexDisplayClipRegionClear() {}

uint32_t vexImageBmpRead(const uint8_t *ibuf, v5_image *oBuf, uint32_t maxw, uint32_t maxh) {}

uint32_t vexImagePngRead(const uint8_t *ibuf, v5_image *oBuf, uint32_t maxw, uint32_t maxh, uint32_t ibuflen) {}

// special use only ! Talk to James.
int32_t vexScratchMemoryPtr(void **ptr) {}

bool vexScratchMemoryLock(void) {}

void vexScratchMemoryUnlock(void) {}

// SD card
FRESULT vexFileMountSD(void) {}

FRESULT vexFileDirectoryGet(const char *path, char *buffer, uint32_t len) {}

FIL *vexFileOpen(const char *filename, const char *mode) {}

FIL *vexFileOpenWrite(const char *filename) {}

FIL *vexFileOpenCreate(const char *filename) {}

void vexFileClose(FIL *fdp) {}

int32_t vexFileRead(char *buf, uint32_t size, uint32_t nItems, FIL *fdp) {}

int32_t vexFileWrite(char *buf, uint32_t size, uint32_t nItems, FIL *fdp) {}

int32_t vexFileSize(FIL *fdp) {}

FRESULT vexFileSeek(FIL *fdp, uint32_t offset, int32_t whence) {}

bool vexFileDriveStatus(uint32_t drive) {}

int32_t vexFileTell(FIL *fdp) {}

void vexFileSync(FIL *fdp) {}

uint32_t vexFileStatus(const char *filename) {}

// CDC
int32_t vexSerialWriteChar(uint32_t channel, uint8_t c) {}

int32_t vexSerialWriteBuffer(uint32_t channel, uint8_t *data, uint32_t data_len) {}

int32_t vexSerialReadChar(uint32_t channel) {}

int32_t vexSerialPeekChar(uint32_t channel) {}

int32_t vexSerialWriteFree(uint32_t channel) {}

// rtos hooks
void vexSystemTimerStop() {}

void vexSystemTimerClearInterrupt() {}

int32_t vexSystemTimerReinitForRtos(uint32_t priority, void (*handler)(void *data)) {}

void vexSystemApplicationIRQHandler(uint32_t ulICCIAR) {}

int32_t vexSystemWatchdogReinitRtos(void) {}

uint32_t vexSystemWatchdogGet(void) {}

// Hooks into the interrupt system, some of these will be used by FreeRTOS
// the others are just placeholders for now
void vexSystemBoot(void) {}

void vexSystemUndefinedException(void) {}

void vexSystemFIQInterrupt(void) {}

void vexSystemIQRQnterrupt(void) {}

void vexSystemSWInterrupt(void) {}

void vexSystemDataAbortInterrupt(void) {}

void vexSystemPrefetchAbortInterrupt(void) {}

// touch
void vexTouchUserCallbackSet(void (*callback)(V5_TouchEvent, int32_t, int32_t)) {}

bool vexTouchDataGet(V5_TouchStatus *status) {}

// system utility
uint32_t vexSystemVersion(void) {}

uint32_t vexStdlibVersion(void) {}

// get SDK version
uint32_t vexSdkVersion(void) {}

// duplication of prototypes in v5_util.h for use by user code
uint32_t vexStdlibVersionLinked(void) {}

bool vexStdlibVersionVerify(void) {}

void vexCompetitionControl(uint32_t data) {}

// battery
int32_t vexBatteryVoltageGet(void) {}

int32_t vexBatteryCurrentGet(void) {}

double vexBatteryTemperatureGet(void) {}

double vexBatteryCapacityGet(void) {}

#pragma clang diagnostic pop