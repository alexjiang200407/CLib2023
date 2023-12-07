#include "array.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

// Dynamic array
struct array
{
	size_t		itemSz;			// Size of the item
	size_t		itemC;			// Number of items in array
	size_t		capacity;		// When number of items passes this value, realloc memory
	Item*		items;			// Items stored by structure, all of the elements stored from 0 to itemC must be on the heap
};

Array ArrayNew(size_t itemSz, size_t startingCapacity)
{
	assert(itemSz != 0);
	assert(startingCapacity != 0);

	Array array = malloc(sizeof(struct array));

	if (!array)
	{
		return NULL;
	}

	array->items = calloc(startingCapacity, sizeof(Item));

	if (!array->items)
	{
		free(array);
		return NULL;
	}

	array->itemSz = itemSz;
	array->capacity = startingCapacity;
	array->itemC = 0;

	return array;
}

void ArrayFree(Array array)
{
	assert(array != NULL);

	// Free each individual item
	for (size_t i = 0; i < array->itemC; i++)
	{
		free(array->items[i]);
	}

	// Free the array of items
	free(array->items);

	free(array);
}

size_t ArrayResize(Array array, size_t size)
{
	assert(array);
	assert(size >= 1);

	// Minimum size is the filled portion of the array
	if (size < array->itemC)
	{
		size = array->itemC;
	}

	Item* resize = realloc(array->items, size * sizeof(Item));

	// Couldn't reallocate memory return 0
	if (!resize)
	{
		return 0;
	}

	// Succedded in reallocating memory, update fields
	array->items = resize;
	array->capacity = size;

	return size;
}

Item ArrayPushBack(Array array, Item item)
{
	assert(array);
	assert(item);

	// Resize array if necessary
	if (array->capacity <= array->itemC)
	{
		if (!ArrayResize(array, array->capacity * 2))
		{
			return NULL;
		}
	}

	// Allocate memory for new item
	array->items[array->itemC] = malloc(array->itemSz);

	// Failed to allocate memory
	if (!array->items[array->itemC])
	{
		return NULL;
	}
	memcpy(array->items[array->itemC], item, array->itemSz);

	return array->items[array->itemC++];
}

Item ArrayPopBack(Array array)
{
	// Nothing to pop
	if (array->itemC == 0)
	{
		return NULL;
	}

	// Resize array if half of the capacity is empty
	if (array->itemC * 2 < array->capacity)
	{
		ArrayResize(array, array->itemC);
	}

	return array->items[--array->itemC];
}

void ArrayPopBackD(Array array)
{
	Item pop = ArrayPopBack(array);

	if (pop)
	{
		free(pop);
	}
}

Item ArrayGet(Array array, size_t index)
{
	assert(index < array->itemC);

	return array->items[index];
}

Item ArrayFront(Array array)
{
	return array->items[0];
}

Item ArrayBack(Array array)
{
	return array->items[array->itemC - 1];
}

size_t* ArraySize(Array array)
{
	return &array->itemC;
}

size_t ArrayCapacity(Array array)
{
	return array->capacity;
}

Item* ArrayData(Array array)
{
	return array->items;
}

size_t ArrayElemSz(Array array)
{
	return array->itemSz;
}
