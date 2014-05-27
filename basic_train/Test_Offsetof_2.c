/**
 *
 *
 */

#include <stdio.h>
#include <stddef.h>

typedef struct book {
    char   name[50];    
    char   author[20];
    char   publish[30];
    char   isbn[20];
    char   local[20];
    int    amount;
    float  price;
	double weight;
    struct book *next;
} BOOK;

#define PR_SIZEOF(_t, _m)       \
        (void)printf("sizeof(%s)=%d\n", #_t "." #_m, (int)sizeof(((_t *)0)->_m))

#define PR_OFFSET(_t, _m)       \
        (void)printf("offset(%s)=%d\n", #_t "." #_m, (int)offsetof(_t, _m))
        
int main(void)
{

		printf("\n");
        PR_SIZEOF(BOOK, name);				// 50
        PR_SIZEOF(BOOK, author);			// 20
        PR_SIZEOF(BOOK, publish);			// 30
        PR_SIZEOF(BOOK, isbn);				// 20
        PR_SIZEOF(BOOK, local);				// 20
        PR_SIZEOF(BOOK, amount);			// 4
        PR_SIZEOF(BOOK, price);				// 4
        PR_SIZEOF(BOOK, weight);			// 8
        PR_SIZEOF(BOOK, next);				// 8

		printf("\n");

        PR_OFFSET(BOOK, name);				// 0
        PR_OFFSET(BOOK, author);			// 50
        PR_OFFSET(BOOK, publish);			// 70
        PR_OFFSET(BOOK, isbn);				// 100
        PR_OFFSET(BOOK, local);				// 120
        PR_OFFSET(BOOK, amount);			// 140
        PR_OFFSET(BOOK, price);				// 144
        PR_OFFSET(BOOK, weight);			// 152
        PR_OFFSET(BOOK, next);				// 160

		printf("\n");

        return (0);
}


