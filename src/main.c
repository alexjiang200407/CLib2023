#include <stdio.h>
#include "vector.h"
#include "stringUtil.h"
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "algorithm.h"
#include "types.h"

int cmpInt(const void* lhs, const void* rhs);

void test1(void);
void test2(void);

int main()
{
	test1();
	test2();
}

void test1(void)
{
	Vector numbers = VecNew(sizeof(int), 1);

	if (!numbers)
	{
		return NULL;
	}

	for (int i = 0; i < 100; i++)
	{
		if (!VecPushBack(numbers, &i))
		{
			return NULL;
		}
	}

	Iter iterator = IterVecNew(numbers, 0, 99);

	if (!iterator)
	{
		return NULL;
	}

	int i = 0;
	int check = 99;
	for (int* num = IterEnd(iterator); num; )
	{
		assert(*num == check);

		if (i++ % 2 == 0)
		{
			num = IterPrev(iterator, 2);
			check -= 2;
		}
		else
		{
			num = IterNext(iterator, 1);
			check += 1;
		}
	}

	IterFree(iterator);
	VecFree(numbers);
}

#define TEST_2_NUMS 50

void test2(void)
{
	Vector numbers = VecNew(sizeof(int), 1);
	srand(time(NULL));

	int arr[TEST_2_NUMS];

	for (int i = 0; i < TEST_2_NUMS; i++)
	{
		int r = rand();
		VecPushBack(numbers, &r);
		arr[i] = r;
		//VecPushBack(numbers, &arr[i]);
	}

	qsort(arr, TEST_2_NUMS, sizeof(int), cmpInt);

	Iter it = IterVecNew(numbers, 0, TEST_2_NUMS - 1);

	quickSort(it, cmpInt);
	

	int* curr = IterStart(it);
	for (int i = 0; i < TEST_2_NUMS; i++, curr = IterNext(it, 1))
	{
		printf("%d %s %d\n", *curr, (*curr == arr[i])? "=" : "=/=", arr[i]);
	}

	IterFree(it);
	VecFree(numbers);
}


int cmpInt(const void* lhs, const void* rhs)
{
	const int* num1 = lhs;
	const int* num2 = rhs;
	return *num1 - *num2;
}