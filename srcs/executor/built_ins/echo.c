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
	{
		arg = arg->next;
		ft_putstr_fd(codee, 1);
		fflush(stderr);
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