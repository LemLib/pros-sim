#include "kapi.h"
#include <pthread.h>
#include <stdint.h>

void rtos_initialize() {}

uint32_t millis(void) {}

uint64_t micros(void) {}

typedef struct {
        task_fn_t func;
        void* parameters;
} task_fn_args;

typedef struct {
        task_fn_args args;
        pthread_t pthread;
        pthread_attr_t pthread_attr;
        uint32_t prio;
        uint16_t stack_depth;
        pthread_t thread;
        const char* name;
} task_t_internal;

void* task_fn_wrapper(const void* parameters) {
    const task_fn_args* args = parameters;
    args->func(args->parameters);
    return 0;
}

task_t task_create(task_fn_t function, void* const parameters, uint32_t prio, const uint16_t stack_depth,
                   const char* const name) {
    task_t_internal* task = malloc(sizeof(task_t_internal));
    task->prio = prio;
    task->stack_depth = stack_depth;
    task->args.func = function;
    task->args.parameters = parameters;
    task->name = name;
    if(pthread_create(&task->thread, &task->pthread_attr, task_fn_wrapper, &task->args)) {
        free(task);
        errno = ENOMEM;
        return 0;
    }
    return task;
}