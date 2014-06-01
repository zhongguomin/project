/**
 *
 */
#include <stdio.h>

char* get_str(void) 
{
	//
	//char str[] = {"abcd"};
	
	//
	char *str = {"abcd"};

	return str;
}

int main(int argc, char *argv[])
{
	char *p = get_str();
	printf("%s\n", p);

	return 0;
}
