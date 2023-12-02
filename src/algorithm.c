#include "algorithm.h"
#include <string.h>

Item* partition(Iter iterator, cmpFn cmp, Item** next);
void swap(Item* lhs, Item* rhs);

void quickSort(Iter iterator, cmpFn cmp)
{ 
	// Base condition end
	if (*IterGetStart(iterator) == *IterGetEnd(iterator))
	{
		return;
	}

	Item* pivotNext = NULL;
	Item* pivotPrev = partition(iterator, cmp, &pivotNext);

	// Sort the upper bound if pivotPrev is defined and isn't last element
	if (pivotNext && *pivotNext != *IterGetEnd(iterator))
	{
		Iter lo = IterCpy(iterator, pivotNext, IterGetEnd(iterator));
		quickSort(lo, cmp);
		IterFree(lo);
	}

	// Sort the lower bound if pivotPrev isn't first element
	if (pivotPrev && *pivotPrev != *IterGetStart(iterator))
	{
		Iter hi = IterCpy(iterator, IterGetStart(iterator), pivotPrev);
		quickSort(hi, cmp);
		IterFree(hi);
	}

}

Item* partition(Iter iterator, cmpFn cmp, Item** next)
{
	Item* pivot = IterGetEnd(iterator);
	Iter  smaller = IterCpy(iterator, IterGetStart(iterator), IterGetEnd(iterator));
	Item* i = NULL;

	for (Item* curr = IterStartP(iterator); curr; curr = IterNextP(iterator, 1))
	{
		// Current element is smaller than pivotPrev
		if (cmp(*curr, *pivot) < 0)
		{
			// Move the iterator that points to the elements smaller than pivotPrev up
			if (i == NULL)
			{
				IterStart(smaller);
				i = IterGetStart(smaller);
			}
			else
			{
				i = IterNextP(smaller, 1);
			}
			// Swap the current element with the largest of smaller portion
			swap(*i, *curr);
		}
	}
	Item* prev = i;

	// Now swap the pivotPrev in place and return it
	if (i == NULL)
	{
		IterStart(smaller);
		i = IterGetStart(smaller);
	}
	else
	{
		i = IterNextP(smaller, 1);
	}
	*next = IterNextP(smaller, 1);

	swap(*i, *pivot);
	IterFree(smaller);
	return prev;
}


void swap(Item* lhs, Item* rhs)
{
	Item temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}