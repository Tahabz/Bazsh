#include "../executor.h"

void pwd(t_arg *arg, char **env)
{
	printf("%s\n", getcwd(*env, 100));
}
