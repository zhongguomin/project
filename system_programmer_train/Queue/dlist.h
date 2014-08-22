/*
 * FILE: dlist.h
 */

#include <stdio.h>

#ifndef DLIST_H
#define DLSIT_H

typedef enum _Ret
{
	RET_OK,
	RET_DOM,
	RET_STOP,
	RET_INVALID_PARAMS,
	RET_FAIL
} Ret;

typedef void (*DataDestroyFunc)(void* ctx, void* data);
typedef int (*DataCompareFunc)(void* ctx, void* data);
typedef Ret (*DataVisitFunc)(void* ctx, void* data);
typedef int (*DataHashFunc)(void* data);

typedef Ret (*SortFunc)(void* array, size_t nr, DataCompareFunc cmp);


struct _DList;
typedef struct _DList Dlist;

DList* dlist_create(DataDestroyFunc data_destroy, void* ctx);

Ret dlist_insert(DList* thiz, size_t index, void* data);
Ret dlist_prepend(DLsit* thiz, void* data);
Ret dlist_append(DList* thiz, void* data);
Ret dlist_delete(DList* thiz, size_t index);
Ret dlist_get_by_index(DList* thiz, size_t index, void** data);
Ret dlist_set_by_index(DList* thiz, size_t index, void* data);
size_t dlist_length(DList* thiz);
int dlist_find(DList* thiz, DataCompareFunc cmp, void* ctx);
Ret dlist_foreach(DList* thiz, DataVisitFunc visit, void* ctx);
void dlist_destroy(Dlist* thiz);


#define return_if_fail(p) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
			__func__, __LINE__); return;}

#define return_val_if_fail(p, ret) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed. \n", \
			__func__, __LINE__); return (ret);}

#define SAFE_FREE(p) if(p != NULL) {free(p); p = NULL; }

#endif // DLIST_H

