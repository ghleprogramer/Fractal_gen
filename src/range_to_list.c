// file holds helper functions to do with creating lists(arrays)
// 	of values in different ways

#include <stdio.h>
#include <stdlib.h>

void centered_rangelist(double list[], double list_center, double range, int size)
{
	// takes array center point range array size
	// sets array elements to ponts inside range centered at center neg to poss
	// returns nothing
	double list_start = list_center - (range / 2);
	for (float i = 0, n = range / size, k = n / 2; i < size; i++)
	{
		list[(int)i] = list_start + k;
		k += n;
	}
}

double *length_rangelist(double range[2], int length)
{
	// creates a list of given length from the start to the end
	// of a given range
	if (range[0] >= range[1])
	{
		return NULL;
	}

	double *list = malloc(sizeof(double) * length);
	if (list == NULL)
	{
		return NULL;
	}

	double range_diff = range[1] - range[0];
	double increase = range_diff / length;
	double n = range[0];
	for (int i = 0; i < length; i++)
	{
		list[i] = n;
		n += increase;
	}
	return list;
}
