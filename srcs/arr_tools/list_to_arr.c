#include "arr_tools.h"

char **list_to_arr(t_arg *arg)
{
	int    args_count;
	char **args;
	int    i;

	args_count = list_count(arg);
	args = (char **) malloc((args_count + 1) * sizeof(char *));
	i = 0;
	while (arg)
	{
		args[i] = arg->val;
		arg = arg->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
