/**
 * strlen()函数用来计算字符串的长度，其原型为：
 *  unsigned int strlen (char *s);
 * strlen()用来计算指定的字符串s 的长度，不包括结束字符"\0"。
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char *str1 = "aaa";
    char str2[100] = "aaaa";
    char str3[5] = "12345";

    printf("strlen(str1)=%d, sizeof(str1)=%d\n", strlen(str1), sizeof(str1));
    printf("strlen(str2)=%d, sizeof(str2)=%d\n", strlen(str2), sizeof(str2));
    printf("strlen(str3)=%d, sizeof(str3)=%d\n", strlen(str3), sizeof(str3));
    
	return 0;
}
