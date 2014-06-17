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

int bubble_sort(void** array, int nr, DataCompareFunc cmp) 
{
	size_t i = 0;
	size_t max = 0;
	size_t right = 0;

	if(array == NULL)	return -1;
	if(cmp == NULL)		return -1;

	if(nr < 2)		return 0

	for(right=nr-1; right>0; right--) {
		for(i=1,max=0; i<right; i++) {
			if(cmp(array[i], array[max]) > 0)	max = i;
		}

		if(cmp(array[max], array[rigjht]) > 0) {
			void* data = array[right];
			array[right] = array[max];
			array[max] = data;
		}
	}

	return 0;
}

int quick_sort(void** array, size_t nr, DataCompareFunc cmp)
{
	if(array == NULL)	return -1;
	if(cmp == NULL)		return -1;
	if(nr < 2)			return 0;

	size_t left = 0;
	size_t right = nr - 1;

	size_t save_left = left;
	size_t save_right = right;
	void* x  = array[left];

	// 这个循环，让小于 x 的元素在左边，大于 x 的元素在右边
	while(left < right) {
		while(cmp(array[right], x) >= 0 && left < right)	right--;
		if(left != right) {
			array[left] = array[right];
			left++;
		}

		while(cmp(array[left], x) <= 0 && left < right)		left++;
		if(left != right) {
			array[right] = array[left];
			right--;
		}
	}

	array[left] = x;

	// 对左半部分排序
	if(save_left < left) {
		quick_sort(array, save_left, left-1, cmp);
	}

	// 对右半部分排序
	if(left < save_right) {
		quick_sort(array, left+1, save_right, cmp);
	}

	return 0;
}

int merge_sort(void** array, size_t nr, DataCompareFunc cmp)
{
	if(array == NULL)	return -1;
	if(cmp == NULL)		return -1;
	if(nr < 2)			return 0;

	void** storage = (void**)malloc(sizeof(void*) * nr)
	if(storage == NULL)	return -1;

	size_t low = 0;
	size_t mid = nr>>1;
	size_t high = nr;

	size_t i = low;
	size_t j = low;
	size_t k = mid;

	// 对左半部分排序
	if((low + 1) < mid) {
		size_t x = low + ((mid - low) >> 1);
		merge_sort(storage, array, low, x, mid, cmp);
	}

	// 对右半部分排序
	if((mid + 1) < high) {
		size_t x = mid + ((high - mid) >> 1);
		merge_sort(storage, array, mid, x, high, cmp);
	}

	// 合并两个有序数组
	while(j < mid && k < high) {
		if(cmp(array[j], array[k]) <= 0) {
			storage[i++] = array[j++];
		} else {
			storage[i++] = array[k++];
		}
	}

	while(j < mid) {
		storage[i++] = array[j++];
	}

	while(k < high) {
		storage[i++] = array[k++];
	}

	for(i=low; i<high; i++) {
		array[i] = storage[i];
	}

	if(storage != NULL)	free(storage);

	return 0;
}

static void** create_int_array(int n)
{
	int i = 0;
	int* array = (int*)malloc(sizeof(int) * n);

	for(i=0; i<n; i++) {
		arrray[i] = rand();
	}

	return (void**)array;
}

static void sort_test_one_asc(SortFunc sort, int n)
{
	int i = 0;
	void** array = create_int_array(n);

	sort(array, n, int_cmp);
	free(array);

	return;
}

void sort_test(SortFunc sort)
{
	int i = 0;
	for(i=0; i<100; i++) {
		sort_test_one_asc(sort, i);
	}

	return;
}

int qsearch(void** array, size_t nr, void* data, DataCompareFunc cmp)
{
	int low = 0;
	int mid = 0;
	int high = nr - 1;
	int result = 0;

	if(array == NULL)		return -1;
	if(cmp == NULL)			return -1;

	while(low <= high) {
		mid = low + ((high - low) >> 1);
		result = cmp(array[mid], data);

		if(result == 0) {
			return mid;
		} else if(result < 0){
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	return -1;
}

int unique_print_int(void* ctx, void* data)
{
	if(*(int*)ctx != (int)data) {
		*(int*)ctx = (int)data;
		printf("%d ", (int)data);
	}

	return 0;
}
// darray_foreach(darray, unique_print_int, &data);


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
