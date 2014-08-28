/*
 *
 */

#ifndef ALLOCATOR_SHMEM_H
#define ALLOCATOR_SHMEM_H

#include "allocator.h"

Allocator* allocator_shmem_create(void* addr, size_t init_size);


#endif // ALLOCATOR_SHMEM_H
