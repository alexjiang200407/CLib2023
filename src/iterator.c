#include "iterator.h"
#include <assert.h>

#define ITERATOR_AT_END   0x1
#define ITERATOR_AT_START 0x2


Item IterNext(Iter iterator, size_t step)
{
	assert(iterator);
	assert(step >= 1);

	// Can't move past end bound
	if (iterator->flags & ITERATOR_AT_END)
	{
		return NULL;
	}

	Item curr = iterator->vtable->get(iterator);
	for (int i = 0; i < step; i++)
	{
		// Can't move past end bound
		if (iterator->flags & ITERATOR_AT_END)
		{
			return NULL;
		}

		curr = iterator->vtable->next(iterator);

		// At the end bound
		if (curr == iterator->end)
		{
			iterator->flags |= ITERATOR_AT_END;
		}
		// No longer at start if we move to the next
		if (iterator->flags & ITERATOR_AT_START)
		{
			iterator->flags ^= ITERATOR_AT_START;
		}
	}
	return curr;
}

Item IterPrev(Iter iterator, size_t step)
{
	assert(iterator);
	assert(step >= 1);

	// Can't move past end bound
	if (iterator->flags & ITERATOR_AT_START)
	{
		return NULL;
	}

	Item curr = iterator->vtable->get(iterator);
	for (int i = 0; i < step; i++)
	{
		// Can't move before start bound
		if (iterator->flags & ITERATOR_AT_START)
		{
			return NULL;
		}

		curr = iterator->vtable->prev(iterator);

		// At the start bound
		if (curr == iterator->start)
		{
			iterator->flags |= ITERATOR_AT_START;
		}
		// No longer at end if we move to the next
		if (iterator->flags & ITERATOR_AT_END)
		{
			iterator->flags ^= ITERATOR_AT_END;
		}
	}
	return curr;
}

Iter IterNew(Item* start, Item* end, IterVtable* vtable, size_t iteratorSz)
{
	assert(iteratorSz != 0);
	assert(vtable != NULL);

	Iter iterator = malloc(iteratorSz);

	if (!iterator)
	{
		return NULL;
	}

	iterator->start = start;
	iterator->end = end;
	iterator->vtable = vtable;

	if (*start == *end)
	{
		iterator->flags = (ITERATOR_AT_END | ITERATOR_AT_START);
	}
	else
	{
		iterator->flags = ITERATOR_AT_START;
	}

	return iterator;
}

Item IterGet(Iter iterator)
{
	assert(iterator);

	Item item = iterator->vtable->get(iterator);

	return item;
}

void IterFree(Iter iterator)
{
	// Frees the memory allocated by the child object
	if (iterator->vtable->free)
	{
		iterator->vtable->free(iterator);
	}

	free(iterator);
}

Item IterEnd(Iter iterator)
{
	// Set the position of the iterator to the end
	iterator->vtable->setPos(iterator, iterator->end);

	// If one element we just update the flags and return
	if (*iterator->start == *iterator->end)
	{
		iterator->flags |= (ITERATOR_AT_END | ITERATOR_AT_START);
		return *iterator->end;
	}

	iterator->flags |= ITERATOR_AT_END;

	// If we were at start previously then we must update the flags
	if (iterator->flags & ITERATOR_AT_START)
	{
		iterator->flags ^= ITERATOR_AT_START;
	}
	
	return *iterator->end;
}

Item IterStart(Iter iterator)
{
	// Set the position of the iterator to the start
	iterator->vtable->setPos(iterator, iterator->start);

	// If one element we just update the flags and return
	if (*iterator->start == *iterator->end)
	{
		iterator->flags |= (ITERATOR_AT_END | ITERATOR_AT_START);
		return *iterator->start;
	}

	iterator->flags |= ITERATOR_AT_START;

	// If we were at start previously then we must update the flags
	if (iterator->flags & ITERATOR_AT_END)
	{
		iterator->flags ^= ITERATOR_AT_END;
	}

	return *iterator->start;
}
