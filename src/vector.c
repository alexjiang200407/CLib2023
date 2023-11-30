#include "vector.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "mutex.h"
//#include <stdatomic.h>


Item IterVecPrev(Iter iterator);
Item IterVecNext(Iter iterator);

struct vector
{
	size_t			itemSz;			// Size of the item
	size_t			itemC;			// Number of items in vector
	size_t			capacity;		// When number of items passes this value, realloc memory
	Item*			items;			// Items stored by structure
	Mutex           lock;			// A lock for threaded safety
};

// Iterator object for quick and easy iteraton
typedef struct vectorIterator
{
	IterVtable* vtable;			// vtable for iterator
	size_t      counter;		// The current position of iterator over counter
	Vector      vector;			// The vector

}* IterVec;


static IterVtable vectorIteratorVtable = {
	.prev = IterVecPrev,
	.next = IterVecNext,
	.free = IterVecFree
};


Vector VecNew(size_t itemSz, size_t startingCapacity)
{
	assert(itemSz != 0);
	assert(startingCapacity != 0);

	Vector vector = malloc(sizeof(struct vector));

	if (!vector)
	{
		return NULL;
	}

	vector->items = calloc(startingCapacity, sizeof(Item));

	if (!vector->items)
	{
		free(vector);
		return NULL;
	}

	vector->itemSz = itemSz;
	vector->capacity = startingCapacity;
	vector->itemC = 0;
	vector->lock = MutexNew();

	return vector;
}

void VecFree(Vector vector)
{
	assert(vector != NULL);

	// Free each individual item
	for (size_t i = 0; i < vector->itemC; i++)
	{
		free(vector->items[i]);
	}

	// Free the array of items
	free(vector->items);

	MutexFree(vector->lock);
	free(vector);
}

size_t VecResize(Vector vector, size_t size)
{
	assert(vector);
	assert(size >= 1);

	MutexLock(vector->lock);

	// Minimum size is the filled portion of the vector
	if (size < vector->itemC)
	{
		size = vector->itemC;
	}

	Item* resize = realloc(vector->items, size * sizeof(Item));

	// Couldn't reallocate memory return 0
	if (!resize)
	{
		MutexUnlock(vector->lock);
		return 0;
	}

	// Succedded in reallocating memory, update fields
	vector->items = resize;
	vector->capacity = size;

	MutexUnlock(vector->lock);
	return size;
}

Item VecPushBack(Vector vector, Item item)
{
	assert(vector);
	assert(item);

	MutexLock(vector->lock);
	
	// Resize vector if necessary
	if (vector->capacity <= vector->itemC)
	{
		if (!VecResize(vector, vector->capacity * 2))
		{
			MutexUnlock(vector->lock);
			return NULL;
		}
	}

	// Allocate memory for new item
	vector->items[vector->itemC] = malloc(vector->itemSz);

	// Failed to allocate memory
	if (!vector->items[vector->itemC])
	{
		MutexUnlock(vector->lock);
		return NULL;
	}
	memcpy(vector->items[vector->itemC], item, vector->itemSz);

	MutexUnlock(vector->lock);
	return vector->items[vector->itemC++];
}

Item VecPopBack(Vector vector)
{
	// Nothing to pop
	if (vector->itemC == 0)
	{
		return NULL;
	}

	MutexLock(vector->lock);
	Item pop = vector->items[--vector->itemC]);
	MutexUnlock(vector->lock);

	return pop;
}

void VecPopBackD(Vector vector)
{
	Item pop = VecPopBack(vector);

	if (pop)
	{
		free(pop);
	}
}

Iter IterVecNew(Vector vector)
{
	assert(vector);

	IterVec iterator = malloc(sizeof(struct vectorIterator));

	if (!iterator)
	{
		return NULL;
	}

	iterator->vtable = &vectorIteratorVtable;
	iterator->counter = 0;
	iterator->vector = vector;

	// Lock the vector to prevent vector from being modified
	if (MutexLock(vector->lock) != 0)
	{
		return NULL;
	}

	return iterator;
}

void IterVecFree(Iter iterator)
{
	assert(iterator);

	IterVec iterVec = iterator;

	// Finished iterating now other threads can modify the vector
	MutexUnlock(iterVec->vector->lock);
}

Item IterVecNext(Iter iterator)
{
	assert(iterator);

	IterVec iterVec = iterator;

	// Iterator is pointing to the endpoints of the vector
	if (iterVec->counter >= iterVec->vector->itemC || iterVec->vector->itemC == 0)
	{
		return NULL;
	}

	return iterVec->vector->items[iterVec->counter++];
}

Item IterVecPrev(Iter iterator)
{
	assert(iterator);

	IterVec iterVec = iterator;

	assert(iterVec->vector);
	assert(iterVec->vtable == vectorIteratorVtable);

	// Iterator is pointing to the endpoints of the vector
	if (iterVec->counter <= 0 || iterVec->vector->itemC == 0)
	{
		return NULL;
	}

	return iterVec->vector->items[iterVec->counter--];
}

Item IterVecGet(Iter iterator)
{
	assert(iterator);

	IterVec iterVec = iterator;

	assert(iterVec->vector);
	assert(iterVec->vtable == vectorIteratorVtable);


	// No elements or out of range
	if (iterVec->vector->itemC == 0 || iterVec->counter >= iterVec->vector->itemC)
	{
		return NULL;
	}

	return iterVec->vector->items[iterVec->counter];
}


Item VecGet(Vector vector, size_t index)
{
	assert(index < vector->itemC);

	return vector->items[index];
}