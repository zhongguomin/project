/*
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef TYPEDEF_H
#define TYPEDEF_H


typedef enum _Ret
{
    RET_OK,
    RET_OOM,
    RET_STOP,
    RET_INVALID_PARAMS,
    RET_FAIL
} Ret;

typedef void (*DataDestroyFunc)(void* ctx, void* data);
typedef int (*DataCompareFunc)(void* ctx, void* data);
typedef Ret (*DataVisitFunc)(void* ctx, void* data);
typedef int (*DataHashFunc)(void* data);

typedef Ret (*SortFunc)(void* array, size_t nr, DataCompareFunc cmp);

#endif //TYPEDEF_H

