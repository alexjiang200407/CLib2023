#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

void testQueue(void);
int cmpInt(Item lhs, Item rhs);
int cmpIntD(Item lhs, Item rhs);

int main(void)
{
	srand(time(NULL));
	testQueue();
	return 0;
}


void testQueue(void)
{
	printf("testing queue data structure: status ");
	PQueue queue = PQNew(sizeof(int), cmpInt);
	int    arrSz = rng(100, 1000);

	if (!PQIsEmpty(queue))
	{
		printf("failed\n");
	}

	int* arr = calloc(arrSz, sizeof(int));
	int insert = rng(0, 1000);
	for (int i = 0; i < arrSz; i++)
	{
		PQInsert(queue, &insert);
		arr[i] = insert;
		insert = rng(0, 1000);
	}

	qsort(arr, arrSz, sizeof(int), cmpIntD);

	// Check the first half of elements
	for (int i = 0; i < arrSz / 2; i++)
	{
		int k = arr[i];
		int* j = PQPop(queue);

		if (*j != k)
		{
			printf("failure\n");
			free(j);
			free(arr);
			PQFree(queue);
			return;
		}
		free(j);
	}

	// Test pop then add
	for (int i = 0; i < arrSz / 2; i++)
	{
		arr[i] = rng(0, 1000);
		PQInsert(queue, &arr[i]);
	}

	qsort(arr, arrSz, sizeof(int), cmpIntD);

	// Check the rest of the elements
	for (int i = 0; i < arrSz; i++)
	{
		int k = arr[i];
		int* j = PQPop(queue);

		if (*j != k)
		{
			printf("failure\n");
			free(j);
			free(arr);
			PQFree(queue);
			return;
		}
		free(j);
	}

	PQFree(queue);
	free(arr);
	printf("success\n");
}



int cmpInt(Item lhs, Item rhs)
{
	return *((int*)lhs) - *((int*)rhs);
}

int cmpIntD(Item lhs, Item rhs)
{
	return -1 * cmpInt(lhs, rhs);
}