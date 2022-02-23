/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:59:37 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:00:50 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*join_path(char *str1, char *str2)
{
	char	*tmp_path;
	char	*joined_path;

	tmp_path = ft_strjoin(str1, "/");
	joined_path = ft_strjoin(tmp_path, str2);
	free(tmp_path);
	return (joined_path);
}

char	*get_command_path(char *command_name, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*command_path;

	if (!*command_name)
		return ("");
	if (command_name[0] == '/')
		return (command_name);
	path = ft_getenv("PATH", env);
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
