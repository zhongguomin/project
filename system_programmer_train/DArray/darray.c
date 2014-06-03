/**
 * 动态数组的实现
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "darray.h"


struct _DArray
{
	void** data;
	int size;
	int alloc_size;

	void* data_destroy_ctx;
	DataDestroyFunc data_destroy;
};

static void darray_destroy_data(DArray* thiz, void* data)
{
    if(thiz->data_destroy != NULL) {
        thiz->data_destroy(thiz->data_destroy_ctx, data);
    }

    return;
}

DArray* darray_create(DataDestroyFunc data_destroy, void* ctx)
{
	DArray* thiz = malloc(sizeof(DArray));

	if(thiz != NULL) {
		thiz->data = NULL;
		thiz->size = 0;
		thiz->alloc_size = 0;
		thiz->data_destroy_ctx = ctx;
		thiz->data_destroy = data_destroy;
	}

	return thiz;
}

#define MIN_PRE_ALLOCATE_NR 10
static int darray_expand(DArray* thiz, int need)
{
	if(thiz == NULL)	return -1;

	if((thiz->size + need) > thiz->alloc_size) {
		int alloc_size = thiz->alloc_size + (thiz->alloc_size>>1) + MIN_PRE_ALLOCATE_NR;

		void** data = (void**)realloc(thiz->data, sizeof(void*) * alloc_size);
		if(data != NULL) {
			thiz->data = data;
			thiz->alloc_size = alloc_size;
		}
	}

	if((thiz->size + need) <= thiz->alloc_size)		return 0;
	else	return -1;
}

int darray_prepend(DArray* thiz, void* data)
{
    return darray_insert(thiz, 0, data);
}

int darray_append(DArray* thiz, void* data)
{
    return darray_insert(thiz, -1, data);
}


/*
------- cursor = -1, thiz->size = 0
======= cursor = 0, thiz->size = 0
------- cursor = -1, thiz->size = 1
======= cursor = 1, thiz->size = 1
------- cursor = -1, thiz->size = 2
======= cursor = 2, thiz->size = 2
------- cursor = -1, thiz->size = 3
======= cursor = 3, thiz->size = 3
------- cursor = -1, thiz->size = 4
======= cursor = 4, thiz->size = 4
------- cursor = -1, thiz->size = 5
======= cursor = 5, thiz->size = 5
*/
int darray_insert(DArray* thiz, int index, void* data)
{
	int ret = -1;
	unsigned int cursor = index;

	if(thiz == NULL)	return -1;
printf("------- cursor = %d, thiz->size = %d\n", cursor, thiz->size);
	cursor = cursor < thiz->size ? cursor : thiz->size;
printf("======= cursor = %d, thiz->size = %d\n", cursor, thiz->size);

	if(darray_expand(thiz, 1) == 0) {
		int i = 0;
		for(i=thiz->size; i>cursor; i--) {
			thiz->data[i] = thiz->data[i-1];
		}

		thiz->data[cursor] = data;
		thiz->size++;

		ret = 0;
	}

	return ret;
}

static int darray_shrink(DArray* thiz)
{
	if(thiz == NULL)	return -1;

	if(thiz->size < (thiz->alloc_size >> 1) && (thiz->alloc_size > MIN_PRE_ALLOCATE_NR)) {
		int alloc_size = thiz->size + (thiz->size >> 1);
		
		void** data = (void**)realloc(thiz->data, sizeof(void*) * alloc_size);
		if(data != NULL) {
			thiz->data = data;
			thiz->alloc_size = alloc_size;
		}
	}

	return 0;
}

int darray_delete(DArray* thiz, int index)
{
	int i = 0;
	int ret = 0;

	if(thiz == NULL)	return -1;
	if(thiz->size < index)	return -1;

	darray_destroy_data(thiz, thiz->data[index]);
	for(i=index; (i+1)<thiz->size; i++) {
		thiz->data[i] = thiz->data[i+1];
	}
	thiz->size--;

	darray_shrink(thiz);

	return 0;
}

int darray_length(DArray* thiz)
{
	if(thiz == NULL)	return 0;

	return thiz->size;
}

int darray_find(DArray* thiz, DataCompareFunc cmp, void* ctx)
{
	int i = 0;

	if(thiz == NULL)	return -1;
	if(cmp == NULL)		return -1;

	for(i=0; i<thiz->size; i++) {
		if(cmp(ctx, thiz->data[i]) == 0)	break;
	}

	return i;
}

int darray_foreach(DArray* thiz, DataVisitFunc visit, void* ctx)
{
	int i = 0;
	int ret = 0;

	if(thiz == NULL)	return -1;
	if(visit == NULL)	return -1;

	for(i=0; i<thiz->size; i++) {
		ret = visit(ctx, thiz->data[i]);
	}

	return ret;
}

void darray_destroy(DArray* thiz)
{
	int i = 0;

	if(thiz != NULL) {
		for(i=0; i<thiz->size; i++) {
			darray_destroy_data(thiz, thiz->data[i]);
		}

		if(thiz->data != NULL) {
			free(thiz->data);
			thiz->data = NULL;
		}

		if(thiz != NULL) {
			free(thiz);
			thiz = NULL;
		}
	}

	return;
}

int darray_get_by_index(DArray* thiz, int index, void** data)
{
	if(thiz == NULL)		return -1;
	if(index > thiz->size)	return -1;
	if(data == NULL)		return -1;

	*data = thiz->data[index];

	return 0;
}

int darray_set_by_index(DArray* thiz, int index, void* data)
{
	if(thiz == NULL)		return -1;
	if(index > thiz->size)	return -1;

	thiz->data[index] = data;

	return 0;
}


