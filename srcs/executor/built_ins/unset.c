#include "../executor.h"

int unset(t_arg *arg, char ***env)
{
	int i;

	if (!arg)
		return (0);
	arg = arg->next;
	while (arg)
	{
		if (!is_ident(arg->val))
		{
			ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
			return (1);
		}
		else
		{
			*env = arr_remove(*env, arg->val);
			// printf("unset %s=%s\n", arg->val, ft_getenv(arg->val, *env));
		}
		arg = arg->next;
	}
	return (0);
}