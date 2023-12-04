#pragma once

#include "v5_apitypes.h"

typedef struct {
    V5_AdiPortConfiguration type;
} emu_adi;

struct _V5_Device {
    V5_DeviceType type;
    union {
        struct {
            V5MotorBrakeMode brakeMode;
            V5MotorControlMode controlMode;
            V5MotorEncoderUnits encoderUnits;
            V5MotorGearset gearset;
            V5_DeviceMotorPid pos_pid, vel_pid;
            int64_t position, velocity;
            int32_t velocity_target;
        } motor;
        struct {
            V5ImuOrientationMode orientationMode;
            V5_DeviceImuRaw rotation;
            V5_DeviceImuRaw acceleration;
        } imu;
        struct {
            double position;
        } rotation, distance;
        struct {
            V5_DeviceOpticalRgb color;
        } optical;
        struct {

        } vision;
        struct {
            V5_DeviceGpsRaw position;
        } gps;
        struct {
            emu_adi adi[8];
        } expander;
    };
};


extern struct _V5_Device emu_smart_ports[];
extern emu_adi emu_adi_ports[];