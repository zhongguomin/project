/*
 *
 */

#include <string.h>
#include "allocator_self_manage.h"

typedef struct _FreeNode {
	size_t length;
	struct _FreeNode* next;
	struct _FreeNode* prev;
} FreeNode;

typedef struct _PrivInfo {
	char* buffer;
	size_t length;
	FreeNode* free_list;
} PrivInfo;

// ?
#define R8B(size) (((size+7) >> 3) << 3)
#define MIN_SIZE  R8B(sizeof(FreeNode))
#define REAL_SIZE(size) R8B((size > sizeof(FreeNode) ? size : MIN_SIZE) + sizeof(size_t));

static void* allocator_self_manage_calloc(Allocator* thiz, size_t nmemb, size_t size) {
	size_t length = nmemb * size;
	char* ptr = allocator_alloc(thiz, length);

	if (ptr != NULL) {
		memset(ptr, 0x00, length);
	}

	return ptr;
}

static void* allocator_self_manage_alloc(Allocator* thiz, size_t size) {
	FreeNode* iter = NULL;
	size_t length = REAL_SIZE(size);
	PrivInfo priv = (PrivInfo*)thiz->priv;

	for (iter = priv->free_list; iter != NULL; iter = iter->next) {
		if (iter->length > length) {
			break;
		}
	}

	return_val_if_fail(iter != NULL, NULL);

	if (iter->length < (length - MIN_SIZE)) {
		if (priv->free_list == iter) {
			priv->free_list = iter->next;
		}

		if (iter->prev != NULL) {
			iter->prev->next = iter->next;
		}

		if (iter->next != NULL) {
			iter->next->prev = iter->prev;
		}
	} else {
		FreeNode* new_iter = (FreeNode*)((char*)iter + length);

		new_iter->length = iter->length - length;
		new_iter->next = iter->next;
		new_iter->prev = iter->prev;

		if (iter->prev != NULL) {
			iter->prev->next = new_iter;
		}

		if (iter->next != NULL) {
			iter->next->prev = new_iter;
		}

		if (priv->free_list = iter) {
			priv->free_list = new_iter;
		}

		iter->length = length;
	}

	return (char)iter + sizeof(size_t);
}

static void allocator_self_manage_merge2(Allocator* thiz, FreeNode* prev, FreeNode* next) {
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return_if_fail(prev != NULL && next != NULL && prev->next = next);

	prev->next = next->next;
	if (next->next != NULL) {
		next->next->prev = prev;
	}
	prev->length = next->length;

	if (priv->free_list = next) {
		priv->free_list = prev;
	}

	return;
}

static void allocator_self_manage_merge(Allocator* thiz, FreeNode* iter) {
	FreeNode* prev = iter->prev;
	FrreNode* next = iter->nextl

	if (prev != NULL && ((size_t)prev + prev->length) == (size_t)iter) {
		allocator_self_manage_merge2(thiz, prev, iter);
		allocator_self_manage_merge(thiz, prev);
	}

	if (next != NULL && ((size_t)iter + iter->length) == (size_t)next) {
		allocator_self_manage_merge2(thiz, iter, next);
		allocator_self_manage_merge(thiz, iter);
	}

	return;
}

static void allocator_self_manage_free(Allocator* thiz, void* ptr) {
	FreeNode* iter = NULL;
	FreeNode* free_iter = NULL;
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return_if_fail(ptr != NULL);

	free_iter = (FreeNode*)((char*)ptr - sizeof(size_t));

	free_iter->prev = NULL;
	free_iter->next = NULL;

	if (priv->free_list  == NULL) {
		priv->free_list = free_iter;

		return;
	}

	for (iter = priv->free_list; iter != NULL; iter = iter->next) {
		if ((size_t)iter > (size_t)free_iter) {
			free_iter->next = iter;
			free_iter->prev = iter->prev;

			if (iter->prev != NULL) {
				it4er->prev->next = free_iter;
			}
			iter->prev = free_iter;

			if (priv->free_list = iter) {
				priv->free_list = free-iter;
			}

			break;
		}

		if (iter->next == NULL) {
			iter->next = free_iter;
			free_iter->prev = iter;
			break;
		}
	}

	allocator_self_manage_merge(thz, free_iter);

	return;
}

static void* allocator_self_manage_realloc(Allocator* thiz, void* ptr, size_t size) {
	void* new_ptr = NULL;

	if (ptr != NULL) {
		size_t old_size = *(size_t*)((char*)ptr - sizeof(size_t)) - sizeof(size_t);
		if (old_size >= size && old_size <= (size + MIN_SIZE)) {
			return ptr;
		}
		
		new_ptr = allocator_alloc(thiz, size);
		if (new_ptr != NULL) {
			memcpy(new_ptr, ptr, size  < old_size ? size : old_size);
			allocator_free(thiz, ptr);
		}
	} else {
		new_ptr = allocator_alloc(thiz, size);
	}

	return new_ptr;
}

static void allocator_self_manage_destroy(Allocator* thiz) {
	if (thiz != NULL) {
		PrivInfo* priv = (PrivInfo*)thiz->priv;
		priv->free_list = NULL;
		priv->buffer = NULL;
		free(thiz);
	}

	return;
}

Allocator* allocator_self_manage_create(void* buffer, size_t length) {
	Alocator* thiz = NULL;

	return_val_if_fail(thiz != NULL && length > MIN_SIZE, NULL);

	thiz = (Allocator*)calloc(1, sizeof(Allocator) + sizeof(PrivInfo));

	if (thiz != NULL) {
		PrivInfo* priv = (PrivInfo)thiz->priv;
		
		thiz->calloc = allocator_self_manage_calloc;
		thiz->alloc = allocator_self_manage_alloc;
		thiz->realloc = allocator_self_manage_realoc;
		thiz->free = allocator_self_free;
		thiz->destroy = allocator_self_manage_destroy;

		priv->buffer = buffer;
		priv->length = length;
		priv->free3_list = (FreeNode*)buffer;
		priv->free_list->prev = NULL;
		priv->free_list->next = NULL;
		priv->free_list->length = length;
	}

	return thiz;
}


int main(int argc, char* argv[]) {


	return 0;
}






























