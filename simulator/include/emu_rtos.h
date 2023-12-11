#pragma once
#include "kapi.h"
#include <pthread.h>
#include <stdint.h>
#include <bits/sigthread.h>
#include <sys/time.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    void (*func)(void*);
    void* parameters;
} task_fn_args;

typedef struct {
    uint32_t magic;
    task_fn_args args;
    pthread_t pthread;
    pthread_attr_t pthread_attr;
    uint32_t prio;
    uint16_t stack_depth;
    pthread_t thread;
    const char* name;
    bool suspended;
    bool deleted;
} task_t_internal;

void task_register(task_t_internal *task);
void task_deregister(task_t_internal *task);
bool task_exists(const char* name);
#ifdef __cplusplus
}
#include <map>
std::map<const char*, task_t_internal*>& get_tasks();
#endif