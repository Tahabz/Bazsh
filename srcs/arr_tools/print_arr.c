#include "arr_tools.h"

void print_2d_arr(char **arr, bool(callback)(char *))
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (callback(arr[i]))
			printf("%s\n", arr[i]);
		i += 1;
	}
}