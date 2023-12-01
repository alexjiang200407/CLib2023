#pragma once
#include "types.h"
#include <stdlib.h>

typedef struct iterator			iterator_t;
typedef struct iteratorVtable	IterVtable;
typedef struct iterator*		Iter;

struct iteratorVtable
{
	Item (*next)(Iter);				// Moves iterator to next element and returns next element
	Item (*prev)(Iter);				// Moves iterator to previous element and returns previous element
	Item (*get)(Iter);				// Gets the current element
	void (*setPos)(Iter, Item*);	// Set the position of the iterator to specified element
	void (*free)(Iter);				// Frees memory allocated by derived objects
};

struct iterator
{
	IterVtable*  vtable;
	Item*        start;
	Item*        end;
	char         flags;
};


/// <summary>
/// Moves the iterator to the next element and then returns the previous element
/// </summary>
/// <param name="iterator">The iterator object.</param>
/// <returns>The previous element that the iterator pointed to</returns>
Item IterNext(Iter iterator, size_t step);

/// <summary>
/// Moves the iterator down and returns the previous element
/// </summary>
/// <param name="iterator">The iterator object.</param>
/// <returns>The previous element that the iterator pointed to</returns>
Item IterPrev(Iter iterator, size_t step);

/// <summary>
/// Creates a new iterator structure, used to create the base object
/// </summary>
/// <param name="start">The start of the iterator</param>
/// <param name="end">The end of the iterator</param>
/// <param name="vtable">The virtual function table</param>
/// <param name="iteratorSz">The actual size of the derived iterator object</param>
/// <returns>New iterator</returns>
Iter IterNew(Item* start, Item* end, IterVtable* vtable, size_t iteratorSz);

/// <summary>
/// Gets the current item pointed by the iterator
/// </summary>
/// <param name="iterator">The specified iterator</param>
/// <returns>The current item pointed by the iterator, NULL if at the endpoints</returns>
Item IterGet(Iter iterator);

/// <summary>
/// Free iterator from the heap
/// </summary>
/// <param name="iterator">The iterator object.</param>
void IterFree(Iter iterator);

/// <summary>
/// Sets the iterator to be at the end point and returns the last element.
/// </summary>
/// <param name="iterator">The specified iterator</param>
/// <returns>The end item of the iterator</returns>
Item IterEnd(Iter iterator);

/// <summary>
/// Sets the iterator to be at the starting point and returns the first element.
/// </summary>
/// <param name="iterator">The specified iterator</param>
/// <returns>The start item of the iterator</returns>
Item IterStart(Iter iterator);
