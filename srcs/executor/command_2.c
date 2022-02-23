/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:39:24 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 16:25:31 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_child_command	is_child_command(char *command_name)
{
	if (!ft_strcmp(command_name, "pwd"))
		return ((t_child_command){true, pwd});
	else if (!ft_strcmp(command_name, "echo"))
		return ((t_child_command){true, echo});
	else if (!ft_strcmp(command_name, "env"))
		return ((t_child_command){true, env});
	return ((t_child_command){false, NULL});
}

t_parent_command	is_parent_command(char *command_name)
{
	if (!ft_strcmp(command_name, "cd"))
		return ((t_parent_command){true, cd});
	else if (!ft_strcmp(command_name, "export"))
		return ((t_parent_command){true, export});
	else if (!ft_strcmp(command_name, "unset"))
		return ((t_parent_command){true, unset});
	return ((t_parent_command){false, NULL});
}

void	handle_in_sequence(t_executor executor, int *fd)
{
	*fd = get_last_fd(executor.command->in_sequence, open_file);
	if (*fd)
	{
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
}

void	handle_out_sequence(t_executor executor, int *fd)
{
	*fd = get_last_fd(executor.command->out_sequence, create_file);
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}
