/**
 *
 */


#ifndef DARRAY_H
#define DARRAY_H

struct _DArray;
typedef struct _DArray DArray;

typedef void (*DataDestroyFunc)(void* ctx, void* data);
typedef int (*DataCompareFunc)(void* ctx, void* data);
typedef int (*DataVisitFunc)(void* ctx, void* data);

DArray* darray_create(DataDestroyFunc data_destroy, void* ctx);

int darray_insert(DArray* thiz, int index, void* data);
int darray_delete(DArray* thiz, int index);
int darray_length(DArray* thiz);

int darray_find(DArray* thiz, DataCompareFunc cmp, void* ctx);
int darray_foreach(DArray* thiz, DataVisitFunc visit, void* ctx);

void darray_destroy(DArray* thiz);

int darray_prepend(DArray* thiz, void*data);
int darray_append(DArray* thiz, void* data);
int drray_get_by_index(DArray* thiz, int index, void** data);
int drray_set_by_index(DArray* thiz, int index, void* data);


// sort
int bubble_sort(void** array, int nr, DataCompareFunc cmp);
int quick_sort(void** array, size_t nr, DataCompareFunc cmp);
int merge_sort(void** array, size_t nr, DataCompareFunc cmp);

#endif	// DARRAY_H
