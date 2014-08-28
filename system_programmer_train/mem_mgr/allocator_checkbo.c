/*
 *
 */

#include <string.h>
#include "allocator_checkbo.h"

#define BEGIN_MAGIC 0xBb
#define END_MAGIC   0xEe

typedef struct _PrivInfo {
	Allocator* real_allocator;
} PrivInfo;

static void* allocator_checkbo_calloc(Allocator* thiz, size_t nmemb, size_t size) {
	void* ptr = NULL;
	size_t total = nmemb * size;

	if (ptr = allocator_alloc(thiz, total) != NULL) {
		memset(ptr, 0x00, total);
	}

	return ptr;
}

static void* allocator_checkbo_alloc(Allocator* thiz, size_t size) {
	char* ptr = NULL;
	size_t total = size + 3 * sizeof(void*);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if ((ptr = allocator_alloc(priv->real_allocator, total)) != NULL) {
		*(size_t*)ptr = size;
		memset(ptr + sizeof(void*) + size, END_MAGIC, sizeof(void*));
	}

	return ptr + 2 * sizeof(void*);
}

static void allocator_checkbo_free(Allocator* thiz, void* ptr) {
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if (priv != NULL) {
		char magic[sizeof(void*)];
		char* real_ptr = (char*)ptr - 2 * sizeof(void*);
		size_t size = *(size_t)(real_ptr);

		memset(magic, BEGIN_MAGIC, sizeof(void*));
		memset(magic, END_MAGIC, sizeof(void*));

		allocator_free(priv->real_allocator, real_ptr);
	}

	return;
}

static void* allocator_checkbo_realloc(Allocator* thiz, void* ptr, size_t size) {
	void* new_ptr = allocator_alloc(thiz, size);
	if (new_ptr != NULL) {
		allocator_free(thiz, ptr);
	}

	return new_ptr;
}

static void* alloctor_checkbo_destroy(Allocator* thiz) {
	if (thiz != NULL) {
		PrivInfo* priv = (PrivInfo*)thiz->priv;
		allocator_destroy(priv->real_alocator);
		free(thiz);
	}

	return;
}

Allocator* allocator_checkbo_create(Allocator* real_allocator) {
	Allocator* thiz = (Allocator*)calloc(1, sizeof(Allocator) + sizeof(PrivInfo));

	if (thiz != NULL) {
		PrivInfo* priv = (PrivInfo)thiz->priv;
		thiz->calloc = allocator_checkbo_calloc;
		thiz->alloc = allocator_checkbo_alloc;
		thiz->realloc = allocator_checkbo_realloc;
		thiz->free = allocator_checkbo_free;
		thiz->destroy = allocator_checkbo_destroy;
		priv->real_allocator = real_allocator;
	}

	return thiz;
}




























