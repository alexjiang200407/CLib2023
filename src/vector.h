#pragma once

#include <stdlib.h>
#include "types.h"

// A vector data structure. Not thread safe
typedef struct vector* Vector;

/// <summary>
/// Creates a new vector structure on the heap
/// </summary>
/// 
/// <param name="itemSz">Size of each item in the vector. Max size when using polymorphism</param>
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
/// Resizes a vector, setting its capacity. Cannot be used when iterating with iterator
/// </summary>
/// 
/// <param name="vector">The vector to resize</param>
/// <param name="capacity">The new capacity of the vector, minimum is 1</param>
/// <returns>Returns the new capacity of the vector. 0 on failure</returns>
size_t VecResize(Vector vector, size_t capacity);

/// <summary>
/// Adds an item to the end of the vector. Cannot be used when iterating with iterator
/// </summary>
/// 
/// <param name="vector">The vector to add to</param>
/// <param name="item">The item to be added. Will be copied onto the heap</param>
/// <returns>The new item added, NULL if no item was added</returns>
Item VecPushBack(Vector vector, Item item);

/// <summary>
/// Removes the item at the end of the vector. Does not destroy the item in the process. Cannot be used when iterating with iterator
/// </summary>
/// 
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
/// Gets an item from stored in a vector
/// </summary>
/// 
/// <param name="vector">The vector to get item out of.</param>
/// <param name="index">Index of the item in the vector</param>
/// <returns></returns>
Item VecGet(Vector vector, size_t index);

/// <summary>
/// Get the front item of the vector
/// </summary>
/// 
/// <param name="vector">The specified vector</param>
/// <returns>The front item of the vector</returns>
Item VecFront(Vector vector);

/// <summary>
/// Get the back item of the vector
/// </summary>
/// 
/// <param name="vector">The specified vector</param>
/// <returns>The back item of the vector</returns>
Item VecBack(Vector vector);

/// <summary>
/// Returns the size of a vector structure.
/// </summary>
/// 
/// <param name="vector">The vector</param>
/// <returns>Pointer to size of the vector</returns>
size_t* VecSize(Vector vector);

/// <summary>
/// Gets the capacity of the vector
/// </summary>
/// <param name="vector">The vector</param>
/// <returns>The capacity of the vector</returns>
size_t VecCapacity(Vector vector);

/// <summary>
/// Gets the data portion of the vector
/// </summary>
/// <param name="vector">The specified vector</param>
/// <returns>The data portion of the vector</returns>
Item* VecData(Vector vector);

/// <summary>
/// Gets the size of elements stored in vector
/// </summary>
/// <param name="vector">The specified vector</param>
/// <returns>Element size</returns>
size_t VecElemSz(Vector vector);
