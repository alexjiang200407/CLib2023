#pragma once
#include <stdlib.h>

// An item is an arbitrary element inside a data structure
typedef const void* Item;

// A comparison function between two abstract types
typedef int (*cmpF)(Item, Item);


