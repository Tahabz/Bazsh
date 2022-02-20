#include "../executor.h"

int cd(t_arg *args, char ***env)
{
	char  arr[100];
	char *arg;

	if (!args->next)
		arg = ft_getenv("HOME", *env);
	else
		arg = ft_strdup(args->next->val);
	if (chdir(arg) == -1)
	{
		free(arg);
		perror("cd");
		return (1);
	}
	free(arg);
	set_env("pwd", getcwd(arr, 100), env);
	return (0);
	// printf("pwd = %s\n", ft_getenv("pwd", *env));
}
