#include "../executor.h"

void unset(t_arg *arg, char ***env)
{
	int i;

	if (!arg)
		return;
	arg = arg->next;
	while (arg)
	{
		if (!is_ident(arg->val))
			ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
		else
		{
			*env = arr_remove(*env, arg->val);
			// printf("unset %s=%s\n", arg->val, ft_getenv(arg->val, *env));
		}
		arg = arg->next;
	}
}