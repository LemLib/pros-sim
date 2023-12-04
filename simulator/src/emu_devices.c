#include "emu_devices.h"

V5_DeviceTypeBuffer emu_smart_port_types;
struct _V5_Device emu_smart_ports[V5_MAX_DEVICE_PORTS];
emu_adi emu_adi_ports [8];

// Generic device
uint32_t vexDevicesGetNumber(void) {}

uint32_t vexDevicesGetNumberByType(V5_DeviceType type) {}

V5_DeviceT vexDevicesGet(void) {}

V5_DeviceT vexDeviceGetByIndex(uint32_t index) {
    return &emu_smart_ports[index];
}

int32_t vexDeviceGetStatus(V5_DeviceType *buffer) {}

int32_t vexDeviceGetTimestamp(V5_DeviceT device) {}

int32_t vexDeviceGetTimestampByIndex(int32_t index) {}



// This is used by the port index functions to map an index to the device pointer
#define VEX_DEVICE_GET(device, index) V5_DeviceT device = vexDeviceGetByIndex(index)
