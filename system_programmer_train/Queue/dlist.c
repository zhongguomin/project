/*
 * File: dlist.c
 */

#include <stdlib.h>
#include "dlist.h"

typedef struct _DListNode
{
	struct _DListNode* prev;
	struct _DListNode* next;
	void* data;
} DListNode;

struct _DList
{
	DListNode* first;
	void* data_destroy_ctx;
	DataDestroyFunc data_destroy;
};


void dlist_destroy_data(DList* thiz, void* data)
{
	if (thiz->data_destroy != NULL) {
		thiz->data_destroy(thiz->data_destroy_ctx, data);
	}

	return;
}

DlistNode* dlist_create_node(DList* thiz, void* data) 
{
	DlistNode* node = malloc(sizeof(DListNode));
	if(node != NULL) {
		node->prev = NULL;
		node->next = NULL;
		node->data = data;
	}

	return node;
}

void dlist_destroy_node(DList* thiz, DListNode* node)
{
	if (node != NULL) {
		node->prev = NULL;
		node->next = NULL;
		dlist_destroy_data(thiz, node->data);
		SAFE_FREE(node);
	}

	return;
}

DList* dlist_create(DataDestroyFunc data_destroy, void* ctx)
{
	DList* thiz = malloc(sizeof(DList));
	if(thiz != NULL) {
		thiz->first = NULL;
		thiz->data_destroy = data_destroy;
		thiz->data_destroy_ctx = ctx;
	}

	return thiz;
}

DListNode* dlist_get_node(DList* thiz, size_t index, int fail_return_last)
{
	DListNode* iter = NULL;
	
	return_val_if_fail(thiz != NULL, NULL);

	iter = thiz->first;
	while(iter != NULL && iter->next != NULL && index > 0) {
		iter = iter->next;
		index--;
	}

	if (!fail_return_last) {
		iter = index > 0 ? NULL : iter;
	}

	return iter;
}

Ret dlist_insert(DList* thiz, size_t index, void* data)
{
	Ret ret = RET_OK;
	DListNode* node = NULL;
	DListNode* cursor = NULL;

	return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

	do {
		if (node = dlist_create_node(thiz, data) == NULL) {
			ret = RET_OOM;
			break;
		}

		if (thiz->first == NULL) {
			thiz->first = node;
			break;
		}

		cursor = dlist_get_node(thiz, index, 1);

		if (index < dlist_length(thiz)) {
			node->next = cursor;
			if (cursor->prev != NULL) {
				cursor->prev->next = node;
			}

			cursor->prev = node;

			if (thiz->first == cursor) {
				thiz->first = node;
			}
		} else {
			cursor->next = node;
			node->prev = cursor;
		}
	} while(0)

	return ret;
}

Ret dlist_prepend(DList* thiz, void* data)
{
	return dlsit_insert(thiz, 0, data);
}

Ret dlist_append(DList* thiz, void* data)
{
	return dlist_insert(thiz, -1, data);
}

Ret dlist_delete(DList* thiz, size_t index)
{
	Ret ret = RET_OK;
	DListNode* cursor = NULL;
	
	return_val_if_return(thiz != NULL, RET_INVALID_PARAMS);

	cursor = dlist_get_node(thiz, index, 0);

	do {
		if (cursor == NULL) {
			ret = RET_INVALID_PARAMS;
			break;
		}

		if (cursor != NULL) {
			if (cursor == thiz->first) {
				thiz->first = cursor->next;
			}

			if (cursor->next != NULL) {
				cursor->next->prev = cursor->prev;
			}

			if (cursor->prev != NULL) {
				cursor->prev->next = cursor->next;
			}

			dlist_destroy_node(thiz, cursor);
		}
	} while(0)
	
	return ret;
}

































