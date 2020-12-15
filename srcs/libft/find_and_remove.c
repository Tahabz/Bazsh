#include "libft.h"

char			*find_and_remove(const char ch, char *arr)
{
	char *new_arr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_arr = (char *)malloc((ft_strlen(arr) - 1) * sizeof(char));
	while (arr[i])
	{
		if (arr[i] != ch)
			new_arr[j] = arr[i];
		i++;
		j++;
	}
	return (new_arr);
}
