#include <math.h>
#include "emu_devices.h"

#define MOTOR_TEMP_MAX 40 //todo

void vexDeviceMotorVelocitySet(V5_DeviceT device, int32_t velocity) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.velocity_target = velocity;
}

void vexDeviceMotorVelocityUpdate(V5_DeviceT device, int32_t velocity) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.velocity_target = velocity;
}

void vexDeviceMotorVoltageSet(V5_DeviceT device, int32_t value) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.voltage = value;
}

int32_t vexDeviceMotorVelocityGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return INT32_MAX;
    return device->motor.velocity_target;
}

double vexDeviceMotorActualVelocityGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return NAN;
    return device->motor.velocity;
}

int32_t vexDeviceMotorDirectionGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return INT32_MAX;
    return device->motor.reverseFlag ? -1 : 1;
}

void vexDeviceMotorModeSet(V5_DeviceT device, V5MotorControlMode mode) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.controlMode = mode;
}

V5MotorControlMode vexDeviceMotorModeGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.controlMode;
}

void vexDeviceMotorPwmSet(V5_DeviceT device, int32_t value) {
    if(device->type != kDeviceTypeMotorSensor) return; // todo figure out what this does
}

int32_t vexDeviceMotorPwmGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
}

void vexDeviceMotorCurrentLimitSet(V5_DeviceT device, int32_t value) {
    if(device->type != kDeviceTypeMotorSensor) return;
}

int32_t vexDeviceMotorCurrentLimitGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.current_max;
}

void vexDeviceMotorVoltageLimitSet(V5_DeviceT device, int32_t value) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.current_max = value;
}

int32_t vexDeviceMotorVoltageLimitGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.voltage_max;
}

void vexDeviceMotorPositionPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.pos_pid = pid;
}

void vexDeviceMotorVelocityPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.vel_pid = pid;
}

int32_t vexDeviceMotorCurrentGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.current;
}

int32_t vexDeviceMotorVoltageGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.voltage;
}

double vexDeviceMotorPowerGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.power;
}

double vexDeviceMotorTorqueGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.torque;
}

double vexDeviceMotorEfficiencyGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.efficiency;
}

double vexDeviceMotorTemperatureGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.temperature;
}

bool vexDeviceMotorOverTempFlagGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return false;
    return device->motor.temperature > MOTOR_TEMP_MAX;
}

bool vexDeviceMotorCurrentLimitFlagGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return false;
    return device->motor.currentLimitFlag;
}

uint32_t vexDeviceMotorFaultsGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return INT32_MAX;
    return device->motor.faults;
}

bool vexDeviceMotorZeroVelocityFlagGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return false;
    return device->motor.zeroVelocityFlag;
}

bool vexDeviceMotorZeroPositionFlagGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return false;
    return device->motor.zeroPositionFlag;
}

uint32_t vexDeviceMotorFlagsGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return INT32_MAX;
    return device->motor.flags;
}

void vexDeviceMotorReverseFlagSet(V5_DeviceT device, bool value) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.reverseFlag = value;
}

bool vexDeviceMotorReverseFlagGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return false;
    return device->motor.reverseFlag;
}

void vexDeviceMotorEncoderUnitsSet(V5_DeviceT device, V5MotorEncoderUnits units) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.encoderUnits = units;
}

V5MotorEncoderUnits vexDeviceMotorEncoderUnitsGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.encoderUnits;
}

void vexDeviceMotorBrakeModeSet(V5_DeviceT device, V5MotorBrakeMode mode) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.brakeMode = mode;
}

V5MotorBrakeMode vexDeviceMotorBrakeModeGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.brakeMode;
}

void vexDeviceMotorPositionSet(V5_DeviceT device, double position) {
    if(device->type != kDeviceTypeMotorSensor) return;
}

double vexDeviceMotorPositionGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return NAN;
    return device->motor.position[0]; //todo
}

int32_t vexDeviceMotorPositionRawGet(V5_DeviceT device, uint32_t *timestamp) {
    if(device->type != kDeviceTypeMotorSensor) return;
}

void vexDeviceMotorPositionReset(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return;
}

double vexDeviceMotorTargetGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return;
}

void vexDeviceMotorServoTargetSet(V5_DeviceT device, double position) {
    if(device->type != kDeviceTypeMotorSensor) return;
}

void vexDeviceMotorAbsoluteTargetSet(V5_DeviceT device, double position, int32_t velocity) {
    if(device->type != kDeviceTypeMotorSensor) return;
}

void vexDeviceMotorRelativeTargetSet(V5_DeviceT device, double position, int32_t velocity) {
    if(device->type != kDeviceTypeMotorSensor) return;
}

void vexDeviceMotorGearingSet(V5_DeviceT device, V5MotorGearset value) {
    if(device->type != kDeviceTypeMotorSensor) return;
    device->motor.gearset = value;
}

V5MotorGearset vexDeviceMotorGearingGet(V5_DeviceT device) {
    if(device->type != kDeviceTypeMotorSensor) return -1;
    return device->motor.gearset;
}

void vexDeviceMotorExternalProfileSet(V5_DeviceT device, double position, int32_t velocity) {
    if(device->type != kDeviceTypeMotorSensor) return;
}
