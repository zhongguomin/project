/****************************************
 *	通用双向链表的实现
 *	DList_Common.c
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include "DList_Common.h"

typedef struct _DListNode
{
	struct _DListNode* prev;
	struct _DListNode* next;
	void* data;
} DListNode;

struct _DList
{
	DListNode* first;
};


DList* dlist_create(void)
{
	DList* thiz = malloc(sizeof(DList));
	if(thiz != NULL)	thiz->first = NULL;

	return thiz;
}

static DListNode* dlist_node_create(void* data)
{
	DListNode* node = malloc(sizeof(DListNode));

	if(node != NULL) {
		node->prev = NULL;
		node->next = NULL;
		node->data = data;
	}

	return node;
}

static DListNode* dlist_get_node(DList* thiz, int index, int fail_return_last)
{
	DListNode* iter = thiz->first;

	while(iter != NULL && iter->next != NULL && index > 0) {
		iter = iter->next;
		index--;
	}

	if(!fail_return_last)	iter = index > 0 ? NULL : iter;

	return iter;
}

int dlist_length(DList* thiz)
{
	int length = 0;
	DListNode* iter = thiz->first;

	while(iter != NULL) {
		length++;
		iter = iter->next;
	}

	return length;
}

int dlist_insert(DList* thiz, int index, void* data)
{
	DListNode* node = NULL;
	DListNode* cursor = NULL;

	if((node = dlist_node_create(data)) == NULL)	return -1;

	if(thiz->first == NULL) {
		thiz->first = node;
		return 0;
	}

	cursor = dlist_get_node(thiz, index, 1);

	if(index < dlist_length(thiz)) {
		if(thiz->first == cursor) {
			thiz->first = node;
		} else {
			cursor->prev->next = node;
			node->prev = cursor->prev;
		}
		node->next = cursor;
		cursor->prev = node;
	} else {
		cursor->next = node;
		node->prev = cursor;
	}

	return 0;
}

static void dlist_node_destroy(DListNode* node)
{
	if(node != NULL) {
		node->next = NULL;
		node->prev = NULL;
		free(node);
	}

	return;
}

int dlist_delete(DList* thiz, int index)
{
	DListNode* cursor = dlist_get_node(thiz, index, 0);

	if(cursor != NULL) {
		if(cursor == thiz->first)	thiz->first = cursor->next;
		if(cursor->next != NULL)	cursor->next->prev = cursor->prev;
		if(cursor->prev != NULL)	cursor->prev->next = cursor->next;

		dlist_node_destroy(cursor);
	}

	return 0;
}

void dlist_destroy(DList* thiz)
{
	DListNode* iter = thiz->first;
	DListNode* next = NULL;

	while(iter != NULL) {
		next = iter->next;
		dlist_node_destroy(iter);
		iter = next;
	}

	thiz->first = NULL;
	free(thiz);

	return;
}

int dlist_find(DList* thiz, DListDataCompareFunc cmp, void* ctx)
{
	int i = 0;
	DListNode* iter = thiz->first;

	while(iter != NULL) {
		if(cmp(ctx, iter->data) == 0)	break;
		i++;
		iter = iter->next;
	}

	return i;
}

int dlist_foreach(DList* thiz, DListDataVisitFunc visit, void* ctx)
{
	int ret = 0;
	DListNode* iter = thiz->first;

	while(iter != NULL && ret != 1) {
		ret = visit(ctx, iter->data);
		iter = iter->next;
	}

	return ret;
}

int dlist_append(DList* thiz, void* data)
{
	return dlist_insert(thiz, -1, data);
}

int dlist_prepend(DList* thiz, void* data)
{
	return dlist_insert(thiz, 0, data);
}

int dlist_get_by_index(DList* thiz, int index, void** data)
{
	DListNode* cursor = dlist_get_node(thiz, index, 0);

	if(cursor != NULL)	*data = cursor->data;

	return cursor != NULL ? 0 : 1;
}

int dlist_set_by_index(DList* thiz, int index, void* data)
{
	DListNode* cursor = dlist_get_node(thiz, index, 0);

	if(cursor != NULL)	cursor->data = data;

	return cursor != NULL ? 0 : 1;
}











