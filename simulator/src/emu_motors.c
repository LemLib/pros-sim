#include "emu_devices.h"

void vexDeviceMotorVelocitySet(V5_DeviceT device, int32_t velocity) {
    if(device->type != V5M)
}

void vexDeviceMotorVelocityUpdate(V5_DeviceT device, int32_t velocity) {}

void vexDeviceMotorVoltageSet(V5_DeviceT device, int32_t value) {}

int32_t vexDeviceMotorVelocityGet(V5_DeviceT device) {}

double vexDeviceMotorActualVelocityGet(V5_DeviceT device) {}

int32_t vexDeviceMotorDirectionGet(V5_DeviceT device) {}

void vexDeviceMotorModeSet(V5_DeviceT device, V5MotorControlMode mode) {}

V5MotorControlMode vexDeviceMotorModeGet(V5_DeviceT device) {}

void vexDeviceMotorPwmSet(V5_DeviceT device, int32_t value) {}

int32_t vexDeviceMotorPwmGet(V5_DeviceT device) {}

void vexDeviceMotorCurrentLimitSet(V5_DeviceT device, int32_t value) {}

int32_t vexDeviceMotorCurrentLimitGet(V5_DeviceT device) {}

void vexDeviceMotorVoltageLimitSet(V5_DeviceT device, int32_t value) {}

int32_t vexDeviceMotorVoltageLimitGet(V5_DeviceT device) {}

void vexDeviceMotorPositionPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid) {}

void vexDeviceMotorVelocityPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid) {}

int32_t vexDeviceMotorCurrentGet(V5_DeviceT device) {}

int32_t vexDeviceMotorVoltageGet(V5_DeviceT device) {}

double vexDeviceMotorPowerGet(V5_DeviceT device) {}

double vexDeviceMotorTorqueGet(V5_DeviceT device) {}

double vexDeviceMotorEfficiencyGet(V5_DeviceT device) {}

double vexDeviceMotorTemperatureGet(V5_DeviceT device) {}

bool vexDeviceMotorOverTempFlagGet(V5_DeviceT device) {}

bool vexDeviceMotorCurrentLimitFlagGet(V5_DeviceT device) {}

uint32_t vexDeviceMotorFaultsGet(V5_DeviceT device) {}

bool vexDeviceMotorZeroVelocityFlagGet(V5_DeviceT device) {}

bool vexDeviceMotorZeroPositionFlagGet(V5_DeviceT device) {}

uint32_t vexDeviceMotorFlagsGet(V5_DeviceT device) {}

void vexDeviceMotorReverseFlagSet(V5_DeviceT device, bool value) {}

bool vexDeviceMotorReverseFlagGet(V5_DeviceT device) {}

void vexDeviceMotorEncoderUnitsSet(V5_DeviceT device, V5MotorEncoderUnits units) {}

V5MotorEncoderUnits vexDeviceMotorEncoderUnitsGet(V5_DeviceT device) {}

void vexDeviceMotorBrakeModeSet(V5_DeviceT device, V5MotorBrakeMode mode) {}

V5MotorBrakeMode vexDeviceMotorBrakeModeGet(V5_DeviceT device) {}

void vexDeviceMotorPositionSet(V5_DeviceT device, double position) {}

double vexDeviceMotorPositionGet(V5_DeviceT device) {}

int32_t vexDeviceMotorPositionRawGet(V5_DeviceT device, uint32_t *timestamp) {}

void vexDeviceMotorPositionReset(V5_DeviceT device) {}

double vexDeviceMotorTargetGet(V5_DeviceT device) {}

void vexDeviceMotorServoTargetSet(V5_DeviceT device, double position) {}

void vexDeviceMotorAbsoluteTargetSet(V5_DeviceT device, double position, int32_t velocity) {}

void vexDeviceMotorRelativeTargetSet(V5_DeviceT device, double position, int32_t velocity) {}

void vexDeviceMotorGearingSet(V5_DeviceT device, V5MotorGearset value) {}

V5MotorGearset vexDeviceMotorGearingGet(V5_DeviceT device) {}

void vexDeviceMotorExternalProfileSet(V5_DeviceT device, double position, int32_t velocity) {}
