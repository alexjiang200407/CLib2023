#pragma once
#include "types.h"

typedef struct iteratorVtable
{
	Item (*next)(Iter);
	Item (*prev)(Iter);
	void (*free)(Iter);
} IterVtable;

typedef struct iterator* Iter;

/// <summary>
/// Gets the next item in the iterator
/// </summary>
/// <param name="iterator">The iterator object.</param>
/// <returns></returns>
Item IterNext(Iter iterator);

/// <summary>
/// Gets the previous item in the iterator
/// </summary>
/// <param name="iterator">The iterator object.</param>
/// <returns></returns>
Item IterPrev(Iter iterator);

/// <summary>
/// Free iterator from the heap
/// </summary>
/// <param name="iterator">The iterator object.</param>
void IterFree(Iter iterator);