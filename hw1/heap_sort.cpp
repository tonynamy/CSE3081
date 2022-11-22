#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <random>

#include "my_types.h"

int HEAP_SORT(ELEMENT data[], int left, int right)
{

	ELEMENT *heap = (ELEMENT *)malloc((right - left + 2) * sizeof(ELEMENT));

	int size = 0;

	for (int i = left; i <= right; i++)
	{
		// push
		heap[++size] = data[i];

		int h_idx = size;

		while (h_idx > 1)
		{
			if (ELEMENT_KEY(&heap[h_idx / 2]) > ELEMENT_KEY(&heap[h_idx]))
			{
				std::swap(heap[h_idx / 2], heap[h_idx]);
			}
			else
			{
				break;
			}

			h_idx /= 2;
		}
	}

	int iter = size;

	while (iter)
	{
		ELEMENT t = heap[1];
		data[left + (size - iter)] = t;

		std::swap(heap[1], heap[iter--]);

		// Adjust
		int a_idx = 1;
		while (a_idx * 2 <= iter)
		{
			int to_idx = a_idx;

			if (ELEMENT_KEY(&heap[a_idx * 2]) < ELEMENT_KEY(&heap[to_idx]))
			{
				to_idx = a_idx * 2;
			}

			if (a_idx * 2 + 1 <= iter && ELEMENT_KEY(&heap[a_idx * 2 + 1]) < ELEMENT_KEY(&heap[to_idx]))
			{
				to_idx = a_idx * 2 + 1;
			}

			if (to_idx == a_idx)
				break;

			std::swap(heap[to_idx], heap[a_idx]);
			a_idx = to_idx;
		}
	}

	free(heap);

	return 1;
}