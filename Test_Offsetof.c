/**
 * 设计一个宏、计算结构体struct中成员的偏移量
 *
 * 问题
 *  OFFSETOF(s, m)的宏定义，s是结构类型，m是s的成员，求m在s中的偏移量。
 *
 *
 *  分析:
 *  我们平时计算一个结构体成员中成员的偏移量，我们会:
 *	struct test te;
 *	printf("%d",(&te.b)-(&te));
 *	所以，我们可以用地址零作为其实地址，强制转换成结构体类型，
 *	然后取出成员的地址，转换成int类型，就可以得到偏移量了。
 *
 *
 * 关于结构体偏移量的学习
 *
 * 关于c语言结构体偏移的一点思考
 * http://m.oschina.net/blog/140463
 *
 * 利用宏来求出结构体成员的一些信息
 * http://www.cnblogs.com/linyilong3/archive/2012/03/30/2425171.html
 *
 * 定义计算变量相对于结构体偏移量的宏
 * http://xinklabi.iteye.com/blog/1545314
 *
 * ５分钟搞定内存字节对齐
 * http://blog.csdn.net/hairetz/article/details/4084088
 */

#include <stdio.h>

#define offsetof(TYPE, MEMBER) (int)&(((TYPE*)0)->MEMBER)

struct _test {
	int a;
	int b;
	int c;
};

typedef struct _test test;

int main(int argc, char *argv[]) {
	printf("%d\n", offsetof(test, c));

	return 0;
}


