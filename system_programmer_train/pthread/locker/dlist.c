/**
 *
 */

#include <stdlib.h>
#include <dlist.h>

typedef struct _DListNode
{
	struct _DListNode* prev;
	struct _DListNode* next;

	void* data;
} DListNode;

struct _DList
{
	Locker* locker;
	DListNode* first;
	void* data_destroy_ctx;
	DListDataDestroyFunc data_destroy;
};


static void dlist_destroy_data(DList* thiz, void* data)
{
	if(thiz->data_destroy != NULL) {
		thiz->data_destroy(thiz->data_destroy_ctx, data);
	}

	return;
}

static DListNode* dlist_create_node(DList* thiz, void* data)
{
	DListNode* node = malloc(sizeof(DListNode));
	if(node != NULL) {
		node->prev = NULL;
		node->next = NULL;
		node->data = data;
	}

	return node;
}

static void dlist_destroy_node(DList* thiz, DListNode* node)
{
	if(node != NULL) {
		node->next = NULL;
		node->prev = NULL;
		dlist_destroy_data(thiz, node->data);
		SAFE_FREE(node);
	}

	return;
}

static void dlist_lock(DList* thiz)
{
	if(thiz->locker != NULL) {
		locker_lock(thiz->locker);
	}

	return;
}

static void dlist_unlock(DList* thiz)
{
	if(thiz->locker != NULL) {
		locker_unlock(thiz->locker);
	}

	return;
}

static void dlist_destroy_locker(DList* thiz)
{
	if(thiz->locker != NULL) {
		locker_unlock(thiz->locker);
		locker_destroy(thiz->locker);
	}

	return;
}

DList* dlist_create(DListDataDestroyFunc data_destroy, void* ctx, Locker* locker)
{
	DList* thiz = malloc(sizeof(DList));
	if(thiz != NULL) {
		thiz->first = NULL;
		thiz->locker = locker;
		thiz->data_destroy = data_destroy;
		thiz->data_destroy_ctx = ctx;
	}

	return thiz;
}

static DListNode* dlist_get_node(DList* thiz, size_t index, int fail_return_last)
{
	DListNode* iter = NULL;

	return_val_if_fail(thiz != NULL, NULL);

	iter = thiz->first;
	while(iter != NULL && iter->next != NULL && index>0) {
		iter = iter->next;
		index--;
	}

	if(!fail_return_last) {
		iter = index>0 > NULL:iter;
	}

	return iter;
}


























