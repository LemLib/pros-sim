/**
 * \file system/system_daemon.c
 *
 * Competition control daemon responsible for invoking the user tasks.
 *
 * Copyright (c) 2017-2021, Purdue University ACM SIGBots
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "kapi.h"
#include "v5_api.h"

extern void vdml_background_processing();

extern void port_mutex_take_all();
extern void port_mutex_give_all();

static task_t competition_task;

static task_t system_daemon_task;

extern void initialize();
extern void competition_initialize();
extern void disabled();
extern void autonomous();
extern void opcontrol();

enum state_task { E_OPCONTROL_TASK = 0, E_AUTON_TASK, E_DISABLED_TASK, E_COMP_INIT_TASK };

char task_names[4][32] = {"User Operator Control (PROS)", "User Autonomous (PROS)", "User Disabled (PROS)",
                          "User Comp. Init. (PROS)"};
task_fn_t task_fns[4] = {opcontrol, autonomous, disabled, competition_initialize};

extern void ser_output_flush(void);

// does the basic background operations that need to occur every 2ms
static inline void do_background_operations() {
	port_mutex_take_all();
	vexBackgroundProcessing();
	vdml_background_processing();
	port_mutex_give_all();
}

static void _system_daemon_task(void* ign) {
	uint32_t time = millis();
	// Initialize status to an invalid state to force an update the first loop
	uint32_t status = (uint32_t)(1 << 8);
	uint32_t task_state;

	// XXX: Delay likely necessary for shared memory to get copied over
	// (discovered b/c VDML would crash and burn)
	// Take all port mutexes to prevent user code from attempting to access VDML during this time. User code could be
	// running if a task is created from a global ctor
	port_mutex_take_all();
	task_delay(2);
	port_mutex_give_all();

	// start up user initialize task. once the user initialize function completes,
	// the _initialize_task will notify us and we can go into normal competition
	// monitoring mode
	competition_task = task_create(initialize, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT,
	                                      "User Initialization (PROS)");

	time = millis();
	while (!task_notify_take(true, 2)) {
		// wait for initialize to finish
		do_background_operations();
	}
	while (1) {
		do_background_operations();

		if (unlikely(status != competition_get_status())) {
			// Have a new competition status, need to clean up whatever's running
			uint32_t old_status = status;
			status = competition_get_status();
			enum state_task state = E_OPCONTROL_TASK;
			if ((status & COMPETITION_DISABLED) && (old_status & COMPETITION_DISABLED)) {
				// Don't restart the disabled task even if other bits have changed (e.g. auton bit)
				continue;
			}

			// competition initialize runs only when entering disabled and we're
			// connected to competition control
			if ((status ^ old_status) & COMPETITION_CONNECTED &&
			    (status & (COMPETITION_DISABLED | COMPETITION_CONNECTED)) == (COMPETITION_DISABLED | COMPETITION_CONNECTED)) {
				state = E_COMP_INIT_TASK;
			} else if (status & COMPETITION_DISABLED) {
				state = E_DISABLED_TASK;
			} else if (status & COMPETITION_AUTONOMOUS) {
				state = E_AUTON_TASK;
			}

			task_state = task_get_state(competition_task);
			// delete the task only if it's in normal operation (e.g. not deleted)
			// The valid task states AREN'T deleted, invalid, or running (running
			// means it's the current task, which will never be the case)
			if (task_state == E_TASK_STATE_READY || task_state == E_TASK_STATE_BLOCKED ||
			    task_state == E_TASK_STATE_SUSPENDED) {
				task_delete(competition_task);
			}

			competition_task = task_create(task_fns[state], NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT,
			                                      task_names[state]);
		}

		task_delay_until(&time, 2);
	}
}

void system_daemon_initialize() {
	system_daemon_task = task_create(_system_daemon_task, NULL, TASK_PRIORITY_MAX - 2, TASK_STACK_DEPTH_DEFAULT,
	                                        "PROS System Daemon");
}



#undef FUNC
