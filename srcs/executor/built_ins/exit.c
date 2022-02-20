#include "../executor.h"

void ft_exit(t_arg *arg, char **env)
{
	arg = arg->next;
	if (!arg)
		exit(status);
	if (!ft_isnum(arg->val))
	{
		ft_putstr_fd("exit\bbazsh: exit: f: numeric argument required\n", 2);
		exit(255);
	}
	if (arg->next)
		ft_putstr_fd("exit\nbazsh: exit: too many arguments\n", 2);
	exit(atoi(arg->val));
}