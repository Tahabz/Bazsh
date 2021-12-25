#include "arr_tools.h"

bool arr_contains(char *arr, char c)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool arr_2d_contains(char **arr, char *str, bool(comparer)(char *, char *))
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (comparer(arr[i], str))
			return (true);
		i += 1;
	}
	return (false);
}