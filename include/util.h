#pragma once
#include <stdlib.h>
#include "types.h"

/// <summary>
/// Formats a buffer.
/// </summary>
/// <param name="fmt">The format of the buffer</param>
/// <param name="bufSz">Returns the size of the new formatted buffer, minus null terminator</param>
/// <returns>A pointer to the buffer on the heap</returns>
char* formatBuf(size_t* bufSz, const char* const fmt, ...);


/// <summary>
/// Generates a random number between start and end
/// </summary>
/// <param name="min">Random number start</param>
/// <param name="max">Random number end</param>
/// <returns>Random number</returns>
int rng(int min, int max);


/// <summary>
/// Copies data on the stack to the heap
/// </summary>
/// <param name="cpy">Copies this to the heap</param>
/// <param name="sz">Size of the copied object on the stack</param>
/// <returns>New object</returns>
void* CpyToHeap(void* cpy, size_t sz);

/// <summary>
/// Swaps two items
/// </summary>
/// <param name="lhs">Item 1</param>
/// <param name="rhs">Item 2</param>
void swap(Item* lhs, Item* rhs);