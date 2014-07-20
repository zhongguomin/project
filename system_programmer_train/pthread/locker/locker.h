/**
 *
 *
 */

#include <typedef.h>

#ifndef LOCKER_H
#define LOCKER_H

struct _Locker;
typedef struct _Locker Locker;

typedef Ret (*LockerLockFunc)(Locker* thiz);
typedef Ret (*LockerUnlockFunc)(Locker* thiz);
typedef Ret (*LockerDestroyFunc)(Locker* thiz);

struct _Locker
{
	LockerLockFunc lock;
	LockerUnlockFunc unlock;
	LockerDestroyFunc destroy;

	char priv[0];
};

static Ret locker_lock(Locker* thiz)
{
	return_val_if_fail(thiz != NULL && thiz->lock != NULL, RET_INVALID_PARAMS);

	return thiz->lock(thiz);
}

static Ret locker_unlock(Locker* thiz)
{
	return_val_if_fail(thiz != NULL && thiz->unlock != NULL, RET_INVALID_PARAMS);

	return thiz->unlock(thiz);
}

static void locker_destroy(locker* thiz)
{
	return_if_fail(thiz != NULL && thiz->destroy != NULL);

	thiz->destroy(thiz);

	return;
}


#endif // LOCKER_H

