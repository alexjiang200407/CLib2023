#pragma once

#include <stdlib.h>
#include "types.h"

#define for_each_in_arr(item, array) \
	int _count = 0; for (Item item = ArrayData(array)[0]; _count < *ArraySize(array); item = ArrayData(array)[++_count])

// A array data structure. Not thread safe
typedef struct array* Array;

/// <summary>
/// Creates a new array structure on the heap
/// </summary>
/// 
/// <param name="itemSz">Size of each item in the array. Max size when using polymorphism</param>
/// <param name="startingCapacity">The starting capacity of the array</param>
/// <returns>New array structure, NULL if failure</returns>
Array ArrayNew(size_t itemSz, size_t startingCapacity);

/// <summary>
/// Frees a array data structure. Assumes all threads have no use for the array.
/// </summary>
/// 
/// <param name="array">The array to free.</param>
void ArrayFree(Array array);

/// <summary>
/// Resizes a array, setting its capacity. Cannot be used when iterating with iterator
/// </summary>
/// 
/// <param name="array">The array to resize</param>
/// <param name="capacity">The new capacity of the array, minimum is 1</param>
/// <returns>Returns the new capacity of the array. 0 on failure</returns>
size_t ArrayResize(Array array, size_t capacity);

/// <summary>
/// Adds an item to the end of the array. Cannot be used when iterating with iterator
/// </summary>
/// 
/// <param name="array">The array to add to</param>
/// <param name="item">The item to be added. Will be copied onto the heap</param>
/// <returns>The new item added, NULL if no item was added</returns>
Item ArrayPushBack(Array array, Item item);

/// <summary>
/// Removes the item at the end of the array. Does not destroy the item in the process. Cannot be used when iterating with iterator
/// </summary>
/// 
/// <returns>The item removed from the array</returns>
/// <param name="array">The array object</param>
Item ArrayPopBack(Array array);

/// <summary>
/// Removes the item at the end of the array. Destroys the item in the process
/// </summary>
/// 
/// <param name="array">The array object</param>
void ArrayPopBackD(Array array);

/// <summary>
/// Gets an item from stored in a array
/// </summary>
/// 
/// <param name="array">The array to get item out of.</param>
/// <param name="index">Index of the item in the array</param>
/// <returns></returns>
Item ArrayGet(Array array, size_t index);

/// <summary>
/// Get the front item of the array
/// </summary>
/// 
/// <param name="array">The specified array</param>
/// <returns>The front item of the array</returns>
Item ArrayFront(Array array);

/// <summary>
/// Get the back item of the array
/// </summary>
/// 
/// <param name="array">The specified array</param>
/// <returns>The back item of the array</returns>
Item ArrayBack(Array array);

/// <summary>
/// Returns the size of a array structure.
/// </summary>
/// 
/// <param name="array">The array</param>
/// <returns>Pointer to size of the array</returns>
size_t* ArraySize(Array array);

/// <summary>
/// Gets the capacity of the array
/// </summary>
/// <param name="array">The array</param>
/// <returns>The capacity of the array</returns>
size_t ArrayCapacity(Array array);

/// <summary>
/// Gets the data portion of the array
/// </summary>
/// <param name="array">The specified array</param>
/// <returns>The data portion of the array</returns>
Item* ArrayData(Array array);

/// <summary>
/// Gets the size of elements stored in array
/// </summary>
/// <param name="array">The specified array</param>
/// <returns>Element size</returns>
size_t ArrayElemSz(Array array);
