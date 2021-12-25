#include "arr_tools.h"

char **arr_remove(char **arr, char *val)
{
	int    i;
	int    j;
	char **new_arr;
	char * var;
	char * var_val;

	var_val = ft_getenv(val, arr);
	if (!var_val)
		return (arr);
	new_arr = (char **) malloc(arr_length(arr) * sizeof(char *));
	i = 0;
	j = 0;
	var = make_env_name(val, var_val);
	free(var_val);
	while (arr[i])
	{
		if (ft_strcmp(arr[i], var))
		{
			new_arr[j] = ft_strdup(arr[i]);
			j += 1;
		}
		i += 1;
	}
	new_arr[j] = val;
	new_arr[j + 1] = NULL;
	free(var);
	free_double_pointer(arr);
	return (new_arr);
}