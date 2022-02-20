#include "../executor.h"

int pwd(t_arg *arg, char **env)
{
	printf("%s\n", getcwd(*env, 100));
	return (0);
}
