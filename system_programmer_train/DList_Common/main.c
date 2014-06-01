/**
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "DList_Common.h"

static int print_int(void* ctx, void* data)
{
	printf("%d ", (int)data);

	return 0;
}

static int sum_cb(void* ctx, void* data)
{
	long* result = ctx;
	*result += (int)data;
}

int main(int argc, char *argv[]) 
{
	int i = 0;
	int n = 10;
	long sum = 0;

	DList* dlist = dlist_create();

	for(i=0; i<n; i++) {
		dlist_append(dlist, (void*)i);
	}

	dlist_foreach(dlist, print_int, NULL);
	dlist_foreach(dlist, sum_cb, &sum);

	printf("\nsum=%d\n", sum);

	dlist_destroy(dlist);

	return 0;
}
