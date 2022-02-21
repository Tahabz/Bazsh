#include "../executor.h"

extern char *codee;

int echo(t_arg *arg, char **env)
{
	int  i;
	bool new_line;

	new_line = true;
	arg = arg->next;
	if (!arg)
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp(arg->val, "-n"))
	{
		arg = arg->next;
		new_line = false;
	}
	else if (!ft_strcmp(arg->val, "?"))
		printf("%s", codee);
	while (arg)
	{
		printf("%s", arg->val);
		if (arg->next)
			printf(" ");
		arg = arg->next;
	}
	return (0);
}