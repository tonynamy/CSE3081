#include <stdio.h>
#include <algorithm>
#include <math.h>

#include "my_types.h"

void _INSERTION_SORT_OPT(ELEMENT data[], int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (ELEMENT_KEY(&data[j]) >= ELEMENT_KEY(&data[j - 1]))
				break;

			std::swap(data[j], data[j - 1]);
		}
	}
}

int medianThree(ELEMENT data[], int a, int b, int c)
{
	if ((ELEMENT_KEY(&data[a]) > ELEMENT_KEY(&data[b])) ^ (ELEMENT_KEY(&data[a]) > ELEMENT_KEY(&data[c])))
		return a;
	else if ((ELEMENT_KEY(&data[b]) < ELEMENT_KEY(&data[a])) ^ (ELEMENT_KEY(&data[b]) < ELEMENT_KEY(&data[c])))
		return b;
	else
		return b;
}

int PARTITION_OPT(ELEMENT data[], int left, int right)
{
	int pivot_idx = medianThree(data, left, (left + right) / 2, right);
	unsigned int pivot = ELEMENT_KEY(&data[pivot_idx]);

	std::swap(data[left], data[pivot_idx]);

	int i = left - 1;
	int j = right + 1;

	while (1)
	{
		i++;
		while (ELEMENT_KEY(&data[i]) < pivot)
		{
			i++;
		}

		j--;
		while (ELEMENT_KEY(&data[j]) > pivot)
		{
			j--;
		}

		if (i >= j)
		{
			return j;
		}

		std::swap(data[i], data[j]);
	}
}

int QUICK_SORT_OPT(ELEMENT data[], int left, int right)
{
	if (left >= right)
	{
		return 1;
	}

	int p;

	while (left < right && right - left > 16)
	{

		p = PARTITION_OPT(data, left, right);

		QUICK_SORT_OPT(data, left, p - 1);

		left = p + 1;
	}

	_INSERTION_SORT_OPT(data, left, right);

	return 1;
}
