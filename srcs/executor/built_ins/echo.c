#include "../executor.h"

extern char *g_code;

void print_args(t_arg *arg)
{
	while (arg)
	{
		printf("%s", arg->val);
		if (arg->next)
			printf(" ");
		arg = arg->next;
	}
}

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
	{
		arg = arg->next;
		ft_putstr_fd(g_code, 1);
		fflush(stderr);
	}
	print_args(arg);
	if (new_line)
		printf("\n");
	return (0);
}