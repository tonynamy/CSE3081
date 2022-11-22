#include <stdio.h>
#include <algorithm>

#include "my_types.h"

int INSERTION_SORT(ELEMENT data[], int left, int right)
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

    return 1;
}