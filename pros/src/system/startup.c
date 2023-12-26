/**
 * \file system/startup.c
 *
 * Contains the main startup code for PROS 3.0. main is called from vexStartup
 * code. Our main() initializes data structures and starts the FreeRTOS
 * scheduler.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdio.h>

#include "v5_api.h"

extern void rtos_initialize();
extern void graphical_context_daemon_initialize();
extern __attribute__((weak)) void display_initialize() {}
extern void vdml_initialize();

void pros_init() {
    rtos_initialize();

	// vfs_initialize();
	//
	vdml_initialize();

	graphical_context_daemon_initialize();
	display_initialize();
}
