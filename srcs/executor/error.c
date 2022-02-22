#include "executor.h"

int p_error(const char *arg, const char *arg2, const char *message, int code)
{
	write(2, "minishell: ", 11);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (arg2)
	{
		write(2, arg2, ft_strlen(arg2));
		write(2, ": ", 2);
	}
	if (message)
		write(2, message, ft_strlen(message));
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	return (code);
}

void handle_errors(char *cmd, char **env)
{
	struct stat dir_stat;

	if (stat(cmd, &dir_stat) == 0 && S_ISDIR(dir_stat.st_mode))
		exit(p_error(cmd, NULL, "is a directory", 126));
	if (errno == 13)
		exit(p_error(cmd, NULL, NULL, 126));
	else if (errno == 8)
		exit(p_error(cmd, NULL, NULL, 1));
	else if (ft_getenv("PATH", env) == NULL)
		exit(p_error(cmd, NULL, NULL, 127));
	else
		exit(p_error(cmd, NULL, "command not found", 127));
}