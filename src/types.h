#pragma once

// An item is an arbitrary element inside a data structure
typedef const void* Item;


// Defines a comparison function for an abstract type
#define DEFINE_CMP_FUNC(type) \
	typedef int (*cmp_##type)(const type, const type);