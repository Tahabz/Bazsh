#include "executor.h"

char *join_path(char *str1, char *str2)
{
	char *tmp_path = ft_strjoin(str1, "/");
	char *joined_path = ft_strjoin(tmp_path, str2);
	free(tmp_path);
	return (joined_path);
}

char *get_command_path(char *command_name, char **env)
{
	char **paths;
	int    i;
	char * command_path;

	if (!*command_name)
		return "";
	if (command_name[0] == '/')
		return (command_name);
	char *path = ft_getenv("PATH", env);
	paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (paths[i])
	{
		command_path = join_path(paths[i], command_name);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		i += 1;
	}
	free_double_pointer(paths);
	return (command_path);
}
