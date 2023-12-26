/**
 * \file devices/vdml.c
 *
 * VDML - VEX Data Management Layer
 *
 * VDML ensures thread saftey for operations on smart devices by maintaining
 * an array of RTOS Mutexes and implementing functions to take and give them.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "vdml/vdml.h"
#include "kapi.h"
#include "v5_api.h"
#include "vdml/registry.h"

#include <errno.h>
#include <stdio.h>

/**
 * Bitmap to indicate if a port has had an error printed or not.
 */
int32_t port_errors;
mutex_t all_port_mutex;

extern void registry_init();
extern void port_mutex_init();

int32_t claim_port_try(uint8_t port, v5_device_e_t type) {
	if (!VALIDATE_PORT_NO(port)) {
		errno = ENXIO;
		return 0;
	}
	if (registry_validate_binding(port, type) != 0) {
		return 0;
	}
	if (!port_mutex_take(port)) {
		errno = EACCES;
		return 0;
	}
	return 1;
}

/**
 * We have V5_MAX_DEVICE_PORTS so that we can do thread safety on things like
 * controllers, batteries which are sort of like smart devices internally to the
 * V5
 */
mutex_t port_mutexes[V5_MAX_DEVICE_PORTS];            // Mutexes for each port

/**
 * Shorcut to initialize all of VDML (mutexes and register)
 */
void vdml_initialize() {
	port_mutex_init();
	registry_init();
    all_port_mutex = mutex_create();
}

/**
 * Initializes the mutexes for the motor ports.
 *
 * Initializes a static array of FreeRTOS mutexes to protect against race
 * conditions. For example, we don't want the Background processing task to run
 * at the same time that we set a motor, because bad information may be
 * returned, or worse.
 */
void port_mutex_init() {
	for (int i = 0; i < V5_MAX_DEVICE_PORTS; i++) {
		port_mutexes[i] = mutex_create();
	}
}

int port_mutex_take(uint8_t port) {
	if (port >= V5_MAX_DEVICE_PORTS) {
		errno = ENXIO;
		return PROS_ERR;
	}
	return mutex_take(port_mutexes[port], TIMEOUT_MAX);
}

int internal_port_mutex_take(uint8_t port) {
	if (port >= V5_MAX_DEVICE_PORTS) {
		errno = ENXIO;
		return PROS_ERR;
	}
	return mutex_take(port_mutexes[port], TIMEOUT_MAX);
}

static inline char* print_num(char* buff, int num) {
	*buff++ = (num / 10) + '0';
	*buff++ = (num % 10) + '0';
	return buff;
}

int port_mutex_give(uint8_t port) {
	if (port >= V5_MAX_DEVICE_PORTS) {
		errno = ENXIO;
		return PROS_ERR;
	}
	return mutex_give(port_mutexes[port]);
}

int internal_port_mutex_give(uint8_t port) {
	if (port >= V5_MAX_DEVICE_PORTS) {
		errno = ENXIO;
		return PROS_ERR;
	}
	return mutex_give(port_mutexes[port]);
}

void port_mutex_take_all() {
    mutex_take(all_port_mutex, TIMEOUT_MAX);
	for (int i = 0; i < V5_MAX_DEVICE_PORTS; i++) {
		port_mutex_take(i);
	}
}

void port_mutex_give_all() {
    mutex_give(all_port_mutex);
	for (int i = 0; i < V5_MAX_DEVICE_PORTS; i++) {
		port_mutex_give(i);
	}
}

void vdml_set_port_error(uint8_t port) {
	if (VALIDATE_PORT_NO(port)) {
		port_errors |= (1 << port);
	}
}

void vdml_unset_port_error(uint8_t port) {
	if (VALIDATE_PORT_NO(port)) {
		port_errors &= ~(1 << port);
	}
}

bool vdml_get_port_error(uint8_t port) {
	if (VALIDATE_PORT_NO(port)) {
		return (port_errors >> port) & 1;
	} else {
		return false;
	}
}

#if 0
void vdml_reset_port_error() {
	port_errors = 0;
}
#endif

/**
 * Background processing function for the VDML system.
 *
 * This function should be called by the system daemon approximately every
 * 2 milliseconds.
 *
 * Updates the registry type array, detecting what devices are actually
 * plugged in according to the system, then compares that with the registry
 * records.
 *
 * On warnings, no operation is performed.
 */
void vdml_background_processing() {

	// Refresh actual device types.
	registry_update_types();
}
