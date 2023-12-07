#pragma once
#include "array.h"
#include <stdbool.h>

typedef struct pqueue* PQueue;

/// <summary>
/// Creates a new priority queue on the heap
/// </summary>
/// <param name="elemSz">The size of the element</param>
/// <param name="cmp">Comparison function</param>
/// <returns>The new priority queue</returns>
PQueue PQNew(size_t elemSz, cmpF cmp);

/// <summary>
/// Checks if a queue is empty
/// </summary>
/// <param name="queue">The specified queue</param>
/// <returns>True if queue is empty false if not</returns>
bool PQIsEmpty(PQueue queue);

/// <summary>
/// Inserts a new element to the priority queue
/// </summary>
/// <param name="queue">The specified queue</param>
/// <param name="insert">The item to copy into the queue</param>
/// <returns>The new item. NULL if not added</returns>
Item PQInsert(PQueue queue, Item insert);

/// <summary>
/// Returns the highest priority item in the priority queue
/// </summary>
/// <param name="queue">The specified queue</param>
/// <returns>Highest priority item</returns>
Item PQPeek(PQueue queue);

/// <summary>
/// Removes the highest priority item in the priority queue
/// </summary>
/// <param name="queue">The specified queue</param>
/// <returns>The highest priority item, which will need to be freed</returns>
Item PQPop(PQueue queue);

/// <summary>
/// Removes an indexed item from the priority queue
/// </summary>
/// <param name="queue">The queue</param>
/// <param name="i">The index of the removed item</param>
/// <returns>The item we just removed, which will need to be freed</returns>
Item PQRemove(PQueue queue, size_t i);

/// <summary>
/// Frees an entire priority queue
/// </summary>
/// <param name="queue">The queue to free</param>
void PQFree(PQueue queue);
