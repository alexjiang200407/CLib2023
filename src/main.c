#include <stdio.h>
#include "vector.h"



int main()
{
	Vector numbers = VecNew(sizeof(int), 1);


	for (int i = 0; i < 100; i++)
	{
		VecPushBack(numbers, &i);
	}

	Iter iterator = IterVecNew(numbers, 0, 99);

	int i = 0;
	for (int* num = IterEnd(iterator); num; )
	{
		printf("%d\n", *num);

		if (i++ % 2 == 0)
		{
			num = IterPrev(iterator, 2);
		}
		else
		{
			num = IterNext(iterator, 1);
		}
	}

	IterFree(iterator);
	VecFree(numbers);
	
	return 0;
}
