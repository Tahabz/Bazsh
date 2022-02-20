#include "../executor.h"

void cd(t_arg *args, char ***env)
{
	char  arr[100];
	char *arg;

	if (!args->next)
		arg = ft_getenv("HOME", *env);
	else
		arg = ft_strdup(args->next->val);
	if (chdir(arg) == -1)
	{
		update_status_code(1);
		free(arg);
		return (perror("cd"));
	}
	free(arg);
	set_env("pwd", getcwd(arr, 100), env);
	// printf("pwd = %s\n", ft_getenv("pwd", *env));
}
