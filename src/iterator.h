#pragma once

#include "types.h"

typedef struct iteratorVtable
{
	Item (*next)(Iter);
	Item (*prev)(Iter);
} IterVtable;

typedef struct iterator* Iter;

Item IterNext(Iter iterator);

Item IterPrev(Iter iterator);

void IterFree(Iter iterator);