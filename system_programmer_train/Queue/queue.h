/*
 *
 *
 */

#include <stdio.h>
#include "typedef.h"

#ifndef QUEUE_H
#define QUEUE_H


struct _Queue;
typedef struct _Queue Queue;

Queue* queue_create(DataDestroyFunc data_destroy, void* data);

Ret queue_head(Queue* thiz, void** data);
Ret queue_push(Queue* thiz, void* data);
Ret queue_pop(Queue* thiz);

size_t queue_length(Queue* thiz);
Ret queue_foreach(Queue* thiz, DataVisitFunc visit, void* ctx);

void queue_destory(Queue* thiz);

#endif //QUEUE_H
