/**
 * DList_Common.h
 *
 */

#ifndef DLIST_COMMON_H
#define DLIST_COMMON_H


struct _DList;
typedef struct _DList DList;

typedef int (*DListDataCompareFunc)(void* ctx, void* data);
typedef int (*DListDataVisitFunc)(void* ctx, void* data);

DList* dlist_create(void);
int dlist_insert(DList* thiz, int index, void* data);
int dlist_delete(DList* thiz, int index);
int dlist_length(DList* thiz);
void dlist_destroy(DList* thiz);

int dlist_append(DList* thiz, void* data);
int dlist_prepend(DList* thiz, void* data);

int dlist_get_by_index(DList* thiz, int index, void** data);
int dlist_get_set_index(DList* thiz, int index, void* data);

int dlist_find(DList* thiz, DListDataCompareFunc cmp, void* ctx);
int dlist_foreach(DList* thiz, DListDataVisitFunc visit, void* ctx);

#endif //DLIST_COMMON_H
