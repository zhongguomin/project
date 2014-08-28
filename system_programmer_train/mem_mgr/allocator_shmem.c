/*
 *
 */

#include <sys/nman.h>
#include "allocator_shmem.h"
#include "allocator_self_manage.h"

typedef struct _PrivInfo {
	char* buffer;
	size_t length;
	Allocator* manager;
} PrivInfo;


static void* allocator_shmem_calloc(Allocator* thiz, size_t nmemb, size_t size) {
	PrivInfo* priv = ()
}

