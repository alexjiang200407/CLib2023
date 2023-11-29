#include "iterator.h"
#include <stdlib.h>

// Base object 'inherited' by all other iterators
struct iterator
{
	IterVtable* vtable;
};

Item IterNext(Iter iterator)
{
	return iterator->vtable->next(iterator);
}

Item IterPrev(Iter iterator)
{
	return iterator->vtable->prev(iterator);
}

void IterFree(Iter iterator)
{
	free(iterator);
}
