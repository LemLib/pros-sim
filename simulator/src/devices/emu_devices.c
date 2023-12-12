#include "emu_devices.h"

struct _V5_Device emu_smart_ports[V5_MAX_DEVICE_PORTS];
emu_adi emu_adi_ports[8];

/**
 * @brief install a new blank smart device into a specific port
 * @param type
 * @param index
 * @return true if successful, false otherwise
 */
bool installDevice(V5_DeviceType type, uint8_t index) {
    if (index >= V5_MAX_DEVICE_PORTS) return false;
    emu_smart_ports[index] = (struct _V5_Device) {
            .exists = 1,
            .type = type
    };
    return true;
}

// Generic device
uint32_t vexDevicesGetNumber() {
    uint8_t count = 0;
    for (uint8_t i = 0; i < V5_MAX_DEVICE_PORTS; i++) {
        if (emu_smart_ports[i].exists) count++;
    }
    return count;
}

uint32_t vexDevicesGetNumberByType(V5_DeviceType type) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < V5_MAX_DEVICE_PORTS; i++) {
        if (emu_smart_ports[i].exists && emu_smart_ports[i].type == type) count++;
    }
    return count;
}

V5_DeviceT vexDevicesGet() {
    return emu_smart_ports;
}

V5_DeviceT vexDeviceGetByIndex(uint32_t index) {
    if (index >= V5_MAX_DEVICE_PORTS) return 0;
    return &emu_smart_ports[index];
}

int32_t vexDeviceGetStatus(V5_DeviceType *buffer) {

}

int32_t vexDeviceGetTimestamp(V5_DeviceT device) {
    return device->timestamp;
}

int32_t vexDeviceGetTimestampByIndex(int32_t index) {
    if (index >= V5_MAX_DEVICE_PORTS) return -1;
    return emu_smart_ports[index].timestamp;
}

// This is used by the port index functions to map an index to the device pointer
#define VEX_DEVICE_GET(device, index) V5_DeviceT device = vexDeviceGetByIndex(index)
