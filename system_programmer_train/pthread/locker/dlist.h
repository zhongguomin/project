/**
 *
 */

#include <stdio.h>
#include <locker.h>

#ifndef DLIST_H
#define DLIST_H


struct _DList;
typedef struct _DList DList;

typedef void (*DListDataDestroyFunc)(void* ctx, void* data);
typedef int (*DListDataCompareFunc)(void* ctx, void* data);
typedef Ret (*DListDataVisitFunc)(void* ctx, void* data);

DList* dlist_create(DListDataDestroyFunc data_destroy, void* ctx, Locker* locker);

Ret dlsit_insert(DList* thiz, size_t index, void* data);
Ret dlist_prepend(DList* thiz, void* data);
Ret dlist_append(DList* thiz, void* data);
Ret dlist_delete(DList* thiz, size_t index);
Ret dlist_get_by_index(DList* thiz, size_t index, void** data);
Ret dlist_set_by_index(DLsit* thiz, size_t index, void* data);

size_t dlist_length(DList* thiz);
int dlist_find(DList* thiz, DListDataCompareFunc cmp, void* ctx);
Ret dlist_foreach(DList* thiz, DListDataVisitFunc visit, void* ctx);

void dlist_destroy(DList* thiz);


#endif // DLIST_H


