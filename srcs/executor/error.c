/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:45:59 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:50:28 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_perror(char *arg, char *msg, int code)
{
	write(2, "minishell: ", 11);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (code);
}

void	catch_errors(char *cmd, char **env)
{
	struct stat	dir_stat;

	if (stat(cmd, &dir_stat) == 0 && S_ISDIR(dir_stat.st_mode))
		exit(ft_perror(cmd, "is a directory", 126));
	if (errno == 13)
		exit(ft_perror(cmd, NULL, 126));
	else if (errno == 8)
		exit(ft_perror(cmd, NULL, 1));
	else if (ft_getenv("PATH", env) == NULL)
		exit(ft_perror(cmd, NULL, 127));
	else
		exit(ft_perror(cmd, "command not found", 127));
}
