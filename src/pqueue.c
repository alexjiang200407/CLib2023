#include "pqueue.h"
#include <assert.h>
#include <stdio.h>
#include "util.h"

typedef struct pqueue
{
	cmpF   cmp;
	Vector data;
};

Item* getParent(Item* array, size_t* index);
void heapifyUp(PQueue queue, size_t i);
void heapifyDown(PQueue queue, size_t i, size_t n);

PQueue PQNew(size_t elemSz, cmpF cmp)
{
	assert(elemSz > 0);
	assert(cmp);

	PQueue queue = malloc(sizeof(struct pqueue));

	if (!queue)
	{
		return NULL;
	}

	// Set the comparison function for pq
	queue->cmp = cmp;
	queue->data = VecNew(elemSz, 1);

	return queue;
}

bool PQIsEmpty(PQueue queue)
{
	assert(queue);

	// If size is 0 then PQ is empty
	return *VecSize(queue->data) == 0;
}

Item PQInsert(PQueue queue, Item insert)
{
	assert(queue);
	assert(insert);

	size_t size = *VecSize(queue->data);

	// Resize the array if capacity equals the size
	if (VecCapacity(queue->data) <= size)
	{
		if (!VecResize(queue->data, 2 * size))
		{
			return NULL;
		}
	}

	Item* array = VecData(queue->data);

	// Copy item from stack to heap
	Item newItem = CpyToHeap(insert, VecElemSz(queue->data));

	if (!newItem)
	{
		return NULL;
	}

	// Add item to array
	array[size] = newItem;

	heapifyUp(queue, size);

	// Increase the vector size by one
	(*VecSize(queue->data))++;

	return newItem;
}

// Returns the pointer to parent element of index and 
// sets index to the index of the parent element
Item* getParent(Item* array, size_t* index)
{
	assert(*index != 0);
	*index = (*index - 1) / 2;

	return &array[*index];
}

Item PQPeek(PQueue queue)
{
	assert(queue);

	// Return the root node which will always have
	// the highest priority
	if (PQIsEmpty(queue))
	{
		return NULL;
	}

	return VecGet(queue->data, 0);
}

Item PQRemove(PQueue queue, size_t i)
{
	assert(i < VecSize(queue->data));

	Item ret = VecGet(queue->data, i);

	Item* data = VecData(queue->data);

	// Reduce size of vector by one
	size_t newSz = --(*VecSize(queue->data));

	// Only one element dont need to do anything
	if (newSz == i)
	{
		return ret;
	}

	bool greaterThan = queue->cmp(data[newSz], data[i]) > 0;
	swap(&data[newSz], &data[i]);

	if (greaterThan)
	{
		heapifyUp(queue, i);
	}
	else
	{
		heapifyDown(queue, i, newSz);
	}

	// Reduce the capacity of the data if it is twice as large as the actual size
	if (VecCapacity(queue->data) >= 2 * newSz)
	{
		VecResize(queue->data, *VecSize(queue->data));
	}

	return ret;
}


Item PQPop(PQueue queue)
{
	return PQRemove(queue, 0);
}

void PQFree(PQueue queue)
{
	VecFree(queue->data);
	free(queue);
}


void heapifyUp(PQueue queue, size_t i)
{
	Item* array = VecData(queue->data);
	while (i != 0)
	{
		int** current = &array[i];
		int** parent = getParent(array, &i);

		// If parent is smaller than current then swap
		if (queue->cmp(*parent, *current) < 0)
		{
			swap(current, parent);
		}
		else
		{
			break;
		}
	}
}

void heapifyDown(PQueue queue, size_t i, size_t n)
{
	Item* data = VecData(queue->data);
	for (; ;)
	{
		// Get the left and right indexs
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t j = i;

		// Left is greater so swap
		if (left < n && queue->cmp(data[left], data[i]) > 0)
		{
			j = left;
		}
		// Right is greater so swap
		if (right < n && queue->cmp(data[right], data[i]) > 0 && queue->cmp(data[left], data[right]) < 0)
		{
			j = right;
		}

		// Both left and right elements are smaller so right position
		if (j == i)
		{
			break;
		}

		swap(&data[i], &data[j]);
		i = j;
	}
}