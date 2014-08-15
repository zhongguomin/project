/**
 * 头文件：#include <string.h>
 * 定义函数：int strncasecmp(const char *s1, const char *s2, size_t n);
 * 函数说明：strncasecmp()用来比较参数s1 和s2 字符串前n个字符，比较时会自动忽略大小写的差异
 * 返回值：若参数s1 和s2 字符串相同则返回0。s1 若大于s2 则返回大于0 的值，s1 若小于s2 则返回小于0 的值
 */
#include <string.h>
#include <stdio.h>

int main(void) {
	char *a = "aBczeF";
	char *b = "AbCdEf";
	size_t cn = 4;

	printf("cmp %d char between %s nad %s\n", cn, a, b);
	if(!strncasecmp(a, b, cn)) {
		printf("	=\n");
	} else {
		printf("	!=\n");
	}

	cn = 3;
	printf("cmp %d char between %s nad %s\n", cn, a, b);
	if(!strncasecmp(a, b, cn)) {
		printf("	=\n");
	} else {
		printf("	!=\n");
	}
}
