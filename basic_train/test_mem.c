/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_str_1()
{
	char str[] = "hello world";
	return str;
}

char* get_str_2()
{
	char* str = "hello world";
	
	return str;
}

char* get_str_3()
{
	char tmp[] = "hello world";
	char* str;
	str = (char*)malloc(12 * sizeof(char));
	memcpy(str, tmp, 12);

	return str;
}

int main(int argc, char* argv[])
{
	char* str_1 = get_str_1();
	char* str_2 = get_str_2();
	char* str_3 = get_str_3();

	printf("str_1 = %s\n", str_1);	
	printf("str_2 = %s\n", str_2);	
	printf("str_3 = %s\n", str_3);

	if(str_3 != NULL) {
		free(str_3);
		str_3 = NULL;
	}

	return 0;
}

