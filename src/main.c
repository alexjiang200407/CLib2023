#include <stdio.h>
#include "vector.h"



int main()
{
	Vector numbers = VecNew(sizeof(int), 1);


	for (int i = 0; i < 100; i++)
	{
		printf("%d\n", *((int*)VecPush(numbers, &i)));
	}


	printf("%d\n", *((int*)VecGet(numbers, 0)));

	Iter iterator = IterVecNew(numbers);
	int* num = IterNext(iterator);

	while (num)
	{
		printf("%d\n", *num);
		num = IterNext(iterator);
	}


	IterFree(iterator);
	VecFree(numbers);
	
	return 0;
}
