#include <vector>

// partitions the array and returns the middle subscript
int partition(std::vector<int>& array, int top, int bottom)
{
	int x = array[top];
	int i = top - 1;
	int j = bottom + 1;

	do
	{
		do
		{
			j--;
		} while (x > array[j]);

		do
		{
			i++;
		} while (x < array[i]);

		if (i < j)
		{
			std::swap(array[i], array[j]);
		}
	} while (i < j);

	return j;
}

void quicksort(std::vector<int>& num, int top, int bottom)
{
	// top = subscript of beginning of array
	// bottom = subscript of end of array

	if (top < bottom)
	{
		int middle = partition(num, top, bottom);
		quicksort(num, top, middle);
		quicksort(num, middle + 1, bottom);
	}
}
