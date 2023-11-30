#include "mutex.h"
#include <stdlib.h>
#include <stdbool.h>


struct mutex
{
	bool locked;
};

Mutex MutexNew()
{
	Mutex mutex = malloc(sizeof(struct mutex));

	mutex->locked = false;

	return mutex;
}

int MutexLock(Mutex mutex)
{
	mutex->locked = true;
	return 0;
}

int MutexUnlock(Mutex mutex)
{
	mutex->locked = false;
	return 0;
}

void MutexFree(Mutex mutex)
{
	free(mutex);
}
