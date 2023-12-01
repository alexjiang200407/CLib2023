#include "vector.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

Item IterVecPrev(Iter iterator);
Item IterVecNext(Iter iterator);
Item IterVecGet(Iter iterator);
void IterVecSetPos(Iter iterator, Item* newPos);


struct vector
{
	size_t		itemSz;			// Size of the item
	size_t		itemC;			// Number of items in vector
	size_t		capacity;		// When number of items passes this value, realloc memory
	Item*		items;			// Items stored by structure
};

// Iterator object for quick and easy iteraton
typedef struct vectorIterator
{
	iterator_t  base;			// base iterator class
	Vector      vector;			// The vector
	Item*		ptr;			// Points to the current item
}* IterVec;


static IterVtable vectorIteratorVtable = {
	.prev = IterVecPrev,
	.next = IterVecNext,
	.get = IterVecGet,
	.setPos = IterVecSetPos,
	.free = NULL
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

Item VecPushBack(Vector vector, Item item)
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

	// Failed to allocate memory
	if (!vector->items[vector->itemC])
	{
		return NULL;
	}
	memcpy(vector->items[vector->itemC], item, vector->itemSz);

	return vector->items[vector->itemC++];
}

Item VecPopBack(Vector vector)
{
	// Nothing to pop
	if (vector->itemC == 0)
	{
		return NULL;
	}

	return vector->items[--vector->itemC];
}

void VecPopBackD(Vector vector)
{
	Item pop = VecPopBack(vector);

	if (pop)
	{
		free(pop);
	}
}

Item VecGet(Vector vector, size_t index)
{
	assert(index < vector->itemC);

	return vector->items[index];
}

Item VecFront(Vector vector)
{
	return vector->items[0];
}

Item VecBack(Vector vector)
{
	return vector->items[vector->itemC - 1];
}

size_t VecSize(Vector vector)
{
	return vector->itemC;
}


Iter IterVecNew(Vector vector, size_t start, size_t end)
{
	assert(vector);
	assert(start >= 0 && start < vector->itemC);
	assert(end >= 0 && end < vector->itemC);
	assert(start <= end);

	// Construct the base object
	IterVec iterator = IterNew(&vector->items[start], &vector->items[end], &vectorIteratorVtable, sizeof(struct vectorIterator));
	if (!iterator)
	{
		return NULL;
	}

	iterator->ptr = &vector->items[start];
	iterator->vector = vector;

	return iterator;
}

Item IterVecNext(Iter iterator)
{
	assert(iterator);

	IterVec iterVec = iterator;

	assert(iterVec->vector);

	// Is the last element, cant go further
	if (iterVec->ptr == &iterVec->vector->items[iterVec->vector->itemC - 1])
	{
		return NULL;
	}

	// Increment pointer to get previous item then return the previous item 
	return *(++iterVec->ptr);
}

Item IterVecPrev(Iter iterator)
{
	assert(iterator);

	IterVec iterVec = iterator;

	assert(iterVec->vector);

	// Is the first element, cant go previous
	if (iterVec->ptr == iterVec->vector->items)
	{
		return NULL;
	}

	Item i = *(--iterVec->ptr);

	// Decrement pointer to get previous item then return the previous item 
	return i;
}

Item IterVecGet(Iter iterator)
{
	assert(iterator);

	IterVec iterVec = iterator;

	return *iterVec->ptr;
}


void IterVecSetPos(Iter iterator, Item* newPos)
{
	assert(iterator);
	assert(newPos);

	IterVec iterVec = iterator;
	iterVec->ptr = newPos;
}

