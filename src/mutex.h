#pragma once

// Stubs


typedef struct mutex* Mutex;

Mutex MutexNew();


int MutexLock(Mutex mutex);


int MutexUnlock(Mutex mutex);


void MutexFree(Mutex mutex);