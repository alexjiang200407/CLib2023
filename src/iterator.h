#pragma once
#include "types.h"
#include <stdlib.h>

typedef struct iterator			iterator_t;
typedef struct iteratorVtable	IterVtable;
typedef struct iterator*		Iter;

struct iteratorVtable
{
	Item* (*next)(Iter);					// Moves iterator to next element and returns next element
	Item* (*prev)(Iter);					// Moves iterator to previous element and returns previous element
	Item* (*get)(Iter);					// Gets the current element
	void  (*setPos)(Iter, Item*);		// Set the position of the iterator to specified element
	void  (*free)(Iter);					// Frees memory allocated by derived objects
	Iter  (*cpy)(Iter, Item*, Item*);	// Creates a deep copy of the iterator over a new range
};

struct iterator
{
	IterVtable*  vtable;			// Virtual function table that will be implemented by derived objects
	Item*        start;				// The start element of the iterator
	Item*        end;				// The end element of iterator
	char         flags;				// The flags
};


/// <summary>
/// Moves the iterator to the next element and then returns the element
/// </summary>
/// <param name="iterator">The iterator object.</param>
/// <param name="step">The step</param>
/// <returns>The previous element that the iterator pointed to</returns>
Item IterNext(Iter iterator, size_t step);

/// <summary>
/// Moves the iterator to the to the next element and returns pointer to it
/// </summary>
/// <param name="iterator">The iterator object</param>
/// <param name="step">The step</param>
/// <returns>Pointer to the next item. Null if at end</returns>
Item* IterNextP(Iter iterator, size_t step);

/// <summary>
/// Moves the iterator down and returns the element
/// </summary>
/// <param name="iterator">The iterator object.</param>
/// <returns>The previous element that the iterator pointed to</returns>
Item IterPrev(Iter iterator, size_t step);

/// <summary>
/// Moves the iterator to the to the previous element and returns pointer to it
/// </summary>
/// <param name="iterator">The iterator object</param>
/// <param name="step">The step</param>
/// <returns>Pointer to the previous item. Null if at start</returns>
Item* IterPrevP(Iter iterator, size_t step);

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

/// <summary>
/// Sets the iterator to be at the starting point and returns pointer to the first element.
/// </summary>
/// <param name="iterator">The specified iterator</param>
/// <returns>The start item of the iterator</returns>
Item* IterStartP(Iter iterator);

/// <summary>
/// Sets the iterator to be at the end point and returns pointer to the first element.
/// </summary>
/// <param name="iterator">The specified iterator</param>
/// <returns>The start item of the iterator</returns>
Item* IterEndP(Iter iterator);

/// <summary>
/// Gets the start element of the iterator
/// </summary>
/// <param name="iterator">The specified iterator</param>
/// <returns>The start element</returns>
Item* IterGetStart(Iter iterator);

/// <summary>
/// Gets the end element of iterator
/// </summary>
/// <param name="iterator">The specified iterator</param>
/// <returns>The end element</returns>
Item* IterGetEnd(Iter iterator);

/// <summary>
/// Copies an iterator with a new start and end range.
/// </summary>
/// <param name="iterator">The iterator to copy</param>
/// <param name="start">The new start of the iterator</param>
/// <param name="end">The new end of the iterator</param>
/// <returns></returns>
Iter IterCpy(Iter iterator, Item* start, Item* end);
