/*
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef enum _Ret {
	RET_OK,
	RET_OOM,
	RET_STOP,
	RET_INVALID_RARAMS,
	RET_FAIL
} Ret;


#define return_if_fail(p) if(!(p)) \
    {printf("%s:%d Warning: "#p" failed.\n", \
        __func__, __LINE__); return;}
#define return_val_if_fail(p, ret) if(!(p)) \
    {printf("%s:%d Warning: "#p" failed.\n",\
    __func__, __LINE__); return (ret);}

#define SAFE_FREE(p) if(p != NULL) {free(p); p = NULL;}


#endif // TYPEDEF_H
