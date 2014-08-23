/*
 * FILE: dlist.h
 */

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"


#ifndef DLIST_H
#define DLSIT_H

struct _DList;
typedef struct _DList DList;

DList* dlist_create(DataDestroyFunc data_destroy, void* ctx);

Ret dlist_insert(DList* thiz, size_t index, void* data);
Ret dlist_prepend(DList* thiz, void* data);
Ret dlist_append(DList* thiz, void* data);
Ret dlist_delete(DList* thiz, size_t index);
Ret dlist_get_by_index(DList* thiz, size_t index, void** data);
Ret dlist_set_by_index(DList* thiz, size_t index, void* data);
size_t dlist_length(DList* thiz);
int dlist_find(DList* thiz, DataCompareFunc cmp, void* ctx);
Ret dlist_foreach(DList* thiz, DataVisitFunc visit, void* ctx);
void dlist_destroy(DList* thiz);


#define return_if_fail(p) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
			__func__, __LINE__); return;}

#define return_val_if_fail(p, ret) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed. \n", \
			__func__, __LINE__); return (ret);}

#define SAFE_FREE(p) if(p != NULL) {free(p); p = NULL; }

#endif // DLIST_H

