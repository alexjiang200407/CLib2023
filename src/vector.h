#pragma once

#include <stdlib.h>
#include "types.h"
#include "iterator.h"

typedef struct vector* Vector;

/// <summary>
/// Creates a new vector structure on the heap
/// </summary>
/// 
/// <param name="itemSz">Size of each item in the vector.</param>
/// <param name="startingCapacity">The starting capacity of the vector</param>
/// <returns>New vector structure, NULL if failure</returns>
Vector VecNew(size_t itemSz, size_t startingCapacity);


/// <summary>
/// Frees a vector data structure. Assumes all threads have no use for the vector.
/// </summary>
/// 
/// <param name="vector">The vector to free.</param>
void VecFree(Vector vector);

/// <summary>
/// Resizes a vector, setting its capacity
/// </summary>
/// 
/// <param name="vector">The vector to resize</param>
/// <param name="capacity">The new capacity of the vector, minimum is 1</param>
/// <returns>Returns the new capacity of the vector. 0 on failure</returns>
size_t VecResize(Vector vector, size_t capacity);


/// <summary>
/// Adds an item to the end of the vector.
/// </summary>
/// 
/// <param name="vector">The vector to add to</param>
/// <param name="item">The item to be added. Will be copied onto the heap</param>
/// <returns>The new item added, NULL if no item was added</returns>
Item VecPushBack(Vector vector, Item item);

/// <summary>
/// Removes the item at the end of the vector. Does not destroy the item in the process
/// </summary>
/// <returns>The item removed from the vector</returns>
/// <param name="vector">The vector object</param>
Item VecPopBack(Vector vector);

/// <summary>
/// Removes the item at the end of the vector. Destroys the item in the process
/// </summary>
/// 
/// <param name="vector">The vector object</param>
void VecPopBackD(Vector vector);


/// <summary>
/// Creates a new iterator for a vector data structure
/// </summary>
/// 
/// <param name="vector"></param>
/// <returns></returns>
Iter IterVecNew(Vector vector);


/// <summary>
/// Gets an item from stored in a vector
/// </summary>
/// 
/// <param name="vector">The vector to get item out of.</param>
/// <param name="index">Index of the item in the vector</param>
/// <returns></returns>
Item VecGet(Vector vector, size_t index);