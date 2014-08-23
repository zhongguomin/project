/*
 *
 */

#include "queue.h"
#include "dlist.h"

struct _Queue {
	DList* dlist;
};

Queue* queue_create(DataDestroyFunc data_destroy, void* ctx)
{
	Queue* thiz = (Queue*)malloc(sizeof(Queue));

	if (thiz != NULL) {
		if ((thiz->dlist = dlist_create(data_destroy, ctx)) == NULL) {
			free(thiz);
			thiz = NULL;
		}
	}

	return thiz;
}

Ret queue_head(Queue* thiz, void** data)
{
	return_val_if_fail(thiz != NULL && data != NULL, RET_INVALID_PARAMS);

	return dlist_get_by_index(thiz->dlist, 0, data);
}

Ret queue_push(Queue* thiz, void* data)
{
	return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

	return dlist_append(thiz->dlist, data);
}

Ret queue_pop(Queue* thiz)
{
	return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

	return dlist_delete(thiz->dlist, 0);
}

size_t queue_length(Queue* thiz)
{
	return_val_if_fail(thiz != NULL, 0);

	return dlist_length(thiz->dlist);
}

Ret queue_foreach(Queue* thiz, DataVisitFunc visit, void* ctx)
{
	return_val_if_fail(thiz != NULL && visit != NULL, RET_INVALID_PARAMS);

	return dlist_foreach(thiz->dlist, visit, ctx);
}

void queue_destroy(Queue* thiz)
{
	if (thiz != NULL) {
		dlist_destroy(thiz->dlist);
		thiz->dlist = NULL;
		free(thiz);
	}

	return;
}

int main(int argc, char* argv[])
{
	printf("This is Queue Main Function ..!!\n");

	return 0;
}

































