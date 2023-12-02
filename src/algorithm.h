#pragma once
#include "iterator.h"
#include "types.h"

typedef (*cmpFn)(Item, Item);

/// <summary>
/// Applies a quick sort on an iterator's range
/// </summary>
/// <param name="iterator">An iterator for a data structure</param>
/// <param name="cmp">Compare the elements of the data structure</param>
void quickSort(Iter iterator, cmpFn cmp);
