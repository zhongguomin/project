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

    struct book *next;
} BOOK;

#define PR_SIZEOF(_t, _m)       \
        (void)printf("sizeof(%s)=%d\n", #_t "." #_m, (int)sizeof(((_t *)0)->_m))

#define PR_OFFSET(_t, _m)       \
        (void)printf("offset(%s)=%d\n", #_t "." #_m, (int)offsetof(_t, _m))
        
int main(void)
{

        PR_SIZEOF(BOOK, name);
        PR_SIZEOF(BOOK, author);
        PR_SIZEOF(BOOK, publish);
        PR_SIZEOF(BOOK, isbn);
        PR_SIZEOF(BOOK, local);
        PR_SIZEOF(BOOK, amount);
        PR_SIZEOF(BOOK, price);
        PR_SIZEOF(BOOK, next);

        PR_OFFSET(BOOK, name);
        PR_OFFSET(BOOK, author);
        PR_OFFSET(BOOK, publish);
        PR_OFFSET(BOOK, isbn);
        PR_OFFSET(BOOK, local);
        PR_OFFSET(BOOK, amount);
        PR_OFFSET(BOOK, price);
        PR_OFFSET(BOOK, next);

        return (0);
}
