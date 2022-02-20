#include "../executor.h"

int echo(t_arg *arg, char **env)
{
	int i;
	int new_line;

	new_line = true;
	arg = arg->next;
	if (!arg)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (!ft_strcmp(arg->val, "-n"))
	{
		arg = arg->next;
		new_line = false;
	}
	while (arg)
	{
		printf("%s", arg->val);
		if (arg->next)
			printf(" ");
		arg = arg->next;
	}
	if (new_line)
		printf("\n");
	return (0);
}