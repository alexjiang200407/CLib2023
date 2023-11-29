#include "vector.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>


Item IterVecPrev(Iter iterator);

Item IterVecNext(Iter iterator);

struct vector
{
	size_t			itemSz;			// Size of the item
	size_t			itemC;			// Number of items in vector
	size_t			capacity;		// When number of items passes this value, realloc memory
	Item*			items;			// Items stored by structure
};

// Iterator object for quick and easy iteraton
typedef struct vectorIterator
{
	IterVtable* vtable;
	size_t      counter;
	Vector      vector;
}* IterVec;

static IterVtable vectorIteratorVtable = {
	.prev = IterVecPrev,
	.next = IterVecNext
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
	free(vector);
}

size_t VecResize(Vector vector, size_t size)
{
	assert(vector);
	assert(size >= 1);

	// Minimum size is the filled portion of the vector
	if (size < vector->itemC)
	{
		size = vector->itemC;
	}

	Item* resize = realloc(vector->items, size * sizeof(Item));

	// Couldn't reallocate memory return 0
	if (!resize)
	{
		return 0;
	}

	// Succedded in reallocating memory, update fields
	vector->items = resize;
	vector->capacity = size;

	return size;
}

Item VecPush(Vector vector, Item item)
{
	assert(vector);
	assert(item);
	
	// Resize vector if necessary
	if (vector->capacity <= vector->itemC)
	{
		if (!VecResize(vector, vector->capacity * 2))
		{
			return NULL;
		}
	}

	// Allocate memory for new item
	vector->items[vector->itemC] = malloc(vector->itemSz);

	// Failed to allocate memory resize to previous
	if (!vector->items[vector->itemC])
	{
		return NULL;
	}
	memcpy(vector->items[vector->itemC], item, vector->itemSz);

	return vector->items[vector->itemC++];
}

Iter IterVecNew(Vector vector)
{
	IterVec iterator = malloc(sizeof(struct vectorIterator));
	if (!iterator)
	{
		return NULL;
	}

	iterator->vtable = &vectorIteratorVtable;
	iterator->counter = 0;
	iterator->vector = vector;

	return iterator;
}

Item IterVecNext(Iter iterator)
{
	IterVec iterVec = iterator;
	if (iterVec->counter >= iterVec->vector->itemC)
	{
		return NULL;
	}

	return iterVec->vector->items[iterVec->counter++];
}

Item IterVecPrev(Iter iterator)
{
	IterVec iterVec = iterator;
	if (iterVec->counter <= 0)
	{
		return NULL;
	}

	return iterVec->vector->items[iterVec->counter--];
}

Item IterVecGet(Iter iterator)
{
	IterVec iterVec = iterator;

	// No elements or out of range
	if (!iterVec->vector->itemC || iterVec->counter >= iterVec->vector->itemC)
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