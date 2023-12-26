#pragma once
#include <errno.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pros/rtos.h"
#include "SDL2/SDL_timer.h"
#ifdef WINNT
#include <windows.h>
#else
#include <pthread.h>
#include <threads.h>
#endif

typedef struct {
    void (*func)(void*);
    void* parameters;
} task_fn_args;

typedef struct {
    uint32_t magic;
    task_fn_args args;
    uint32_t prio;
    uint16_t stack_depth;
    const char* name;
    bool suspended;
    bool deleted;
    pthread_attr_t pthread_attr;
    pthread_t thread;
    void* mutex;
    pthread_condattr_t condAttr;
    pthread_cond_t resumeCond;
    uint32_t ulNotifiedValue;
    uint8_t ucNotifyState;
} task_t_internal;

typedef struct {
    uint32_t magic;
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;
    bool deleted;
} mutex_t_internal;
#ifdef __cplusplus
extern "C" {
#endif
void task_register(task_t_internal *task);
void task_deregister(task_t_internal *task);
bool task_exists(const char* name);

#ifdef __cplusplus
}
#endif