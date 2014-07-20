/**
 * test_thread_01.c
 *
 *	gcc -lpthread -o test_thread_01 test_thread_01.c
 */

#include <stdio.h>
#include <pthread.h>
#include <assert.h>

char str2[] = "for test";

void* start_routine(void* param)
{
	char* str = (char*)param;
	printf("%s:%s\n", __func__, str);
	return NULL;
}

pthread_t create_test_thread()
{
	pthread_t id = 0;
	char str[] = "is is ok";
	
	pthread_create(&id, NULL, start_routine, str);
	//pthread_create(&id, NULL, start_routine, str2);
	
	return id;
}

int main(int argc, char* argv[])
{
	void* ret = NULL;
	pthread_t id = create_test_thread();
	pthread_join(id, &ret);

	return 0;
}

