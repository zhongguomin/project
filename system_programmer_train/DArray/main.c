/**
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "darray.h"


static int int_cmp(void* ctx, void* data)
{
	return (int)data - (int)ctx;
}

static int print_int(void* ctx, void* data)
{
	printf("%d ", (int)data);

	return 0;
}

static int check_and_dec_int(void* ctx, void* data)
{
	int* expected = (int*)ctx;
	(*expected)--;

	return 0;
}

int main(int argc, char* argv[])
{
	int i = 0;
	int n = 10;
	int data = 0;

	DArray* darray = darray_create(NULL, NULL);

	for(i=0; i<n; i++) {
		darray_append(darray, (void*)i);
	}

	darray_foreach(darray, print_int, NULL);
	printf("\n");
	//printf("size = %d, alloc_size = %d\n", darray->size, darray->alloc_size);

	darray_destroy(darray);

	return 0;
}
