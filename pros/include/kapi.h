/**
 * \file kapi.h
 *
 * Kernel API header
 *
 * Contains additional declarations for use internally within kernel
 * development. This file includes the FreeRTOS header, which allows for
 * creation of statically allocated FreeRTOS primitives like tasks, semaphores,
 * and queues.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "api.h"
#include "pros/apix.h"

#define unlikely(cond) __builtin_expect(!!(cond), 0)

#ifdef __cplusplus
extern "C" {



#define task_t pros::task_t
#define task_fn_t pros::task_fn_t
#define mutex_t pros::mutex_t
#define sem_t pros::c::sem_t
#define queue_t pros::c::queue_t
#endif

#define warn_printf(fmt, ...) dprintf(STDERR_FILENO, "%s:%d -- " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define warn_wprint(str) wprintf("%s", str)

#define kprintf(fmt, ...) dprintf(STDOUT_FILENO, "%s:%d -- " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define kprint(str) kprintf("%s", str)

#ifndef PROS_RELEASING
#define kassert(cond)                     \
	do {                                    \
		if (!(cond)) {                        \
			kprint("Assertion failed: " #cond); \
		}                                     \
	} while (0)
#else
#define kassert(cond)
#endif

typedef uint32_t task_stack_t;

/**
 * Suspends the scheduler without disabling interrupts. context switches will
 * not occur while the scheduler is suspended. RTOS ticks that occur while the
 * scheduler is suspended will be held pending until the scheduler has been
 * unsuspended with rtos_resume_all()
 *
 * When used correctly, this function ensures that operations occur atomically
 * w.r.t. multitasking. Functions like task_delay, queue_send, and other
 * functions MUST NOT be called while the scheduler is disabled.
 */
void rtos_suspend_all();

/**
 * Resumes the scheduler. It does not resume unsuspended tasks that were
 * previously suspended by task_suspend.
 *
 * if(rtos_resume_all()) {
 *     task_delay(0); // force context switch
 * }
 * \return True if a context switch is necessary.
 */
int32_t rtos_resume_all();


/**
 * Creates a statically allocated queue.
 *
 * All FreeRTOS primitives must be created statically if they are required for
 * operation of the kernel.
 *
 * \param length
 *        The maximum number of items that the queue can contain.
 * \param item_size
 *        The number of bytes each item in the queue will require.
 * \param[out] storage_buffer
 *             A memory location for data storage
 * \param[out] queue_buffer
 *             A buffer to store the queue in
 *
 * \return A handle to a newly created queue, or NULL if the queue cannot be
 * created.
 */
queue_t queue_create_static(uint32_t length, uint32_t item_size, uint8_t* storage_buffer,
                            queue_t* queue_buffer);


/**
 * Display a fatal error to the built-in LCD/touch screen.
 *
 * This function is intended to be used when the integrity of the RTOS cannot be
 * trusted. No thread-safety mechanisms are used and this function only relies
 * on the use of the libv5rts.
 *
 * \param[in] text
 *            The text string to display to the screen
 */
void display_fatal_error(const char* text);

/**
 * Prints hex characters to the terminal.
 *
 * \param[in] s
 *            The array of hex characters to print
 * \param len
 *        The number of hex characters to print
 */
void kprint_hex(uint8_t* s, size_t len);

#ifdef __cplusplus
#undef task_t
#undef task_fn_t
#undef mutex_t
}
#endif
