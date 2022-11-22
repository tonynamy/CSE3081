#include <stdio.h>
#include <algorithm>

#include "my_types.h"

int PARTITION(ELEMENT data[], int left, int right)
{
	int i, pivot;
	pivot = left;
	for (i = left; i < right; i++)
	{
		if (ELEMENT_KEY(&data[i]) < ELEMENT_KEY(&data[right]))
		{
			std::swap(data[i], data[pivot]);
			pivot++;
		}
	}
	std::swap(data[right], data[pivot]);
	return (pivot);
}

int QUICK_SORT(ELEMENT data[], int left, int right)
{

	int pivot;
	if (right - left > 0)
	{
		pivot = PARTITION(data, left, right);
		QUICK_SORT(data, left, pivot - 1);
		QUICK_SORT(data, pivot + 1, right);
	}
	return 1;
}