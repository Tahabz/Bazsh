/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:36:27 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 16:36:12 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exec_child_command(t_executor executor_state, char **env)
{
	int		fd;
	char	**command_args;

	command_args = list_to_arr(executor_state.command->arg);
	signal(SIGINT, SIG_DFL);
	if (!ft_strcmp(executor_state.command->arg->val, "exit"))
		ft_exit(executor_state.command->arg, env);
	if (executor_state.command->in_sequence)
		handle_in_sequence(executor_state, &fd);
	else if (executor_state.command_position > 0)
		dup_and_close(executor_state.old_fd, STDIN_FILENO);
	if (executor_state.command->out_sequence
		&& executor_state.command->out_sequence->type != IO_PIPE)
		handle_out_sequence(executor_state, &fd);
	else if (executor_state.command->next)
		dup_and_close(executor_state.new_fd, STDOUT_FILENO);
	exec_command(executor_state, env);
}

void	replace_fds(t_executor *executor)
{
	executor->old_fd[0] = executor->new_fd[0];
	executor->old_fd[1] = executor->new_fd[1];
}

void	exec_parent_command(t_executor *executor,
t_parent_command command, char ***env)
{
	executor->command_position -= 1;
	set_status_code(command.handler(executor->command->arg, env));
}

void	handle_command(t_executor *executor_state, char ***env)
{
	t_parent_command	command;

	if (!executor_state->command->arg)
	{
		executor_state->command_position -= 1;
		return ;
	}
	command = is_parent_command(executor_state->command->arg->val);
	if (command.is_parent_command)
		return (exec_parent_command(executor_state, command, env));
	else if (!ft_strcmp(executor_state->command->arg->val, "exit")
		&& !executor_state->command->next)
		ft_exit(executor_state->command->arg, *env);
	if (executor_state->command->next)
		pipe(executor_state->new_fd);
	g_signal.forked = true;
	executor_state->pids[executor_state->command_position] = fork();
	if (executor_state->pids[executor_state->command_position] == 0)
		exec_child_command(*executor_state, *env);
	if (executor_state->command_position > 0)
		close_fd(executor_state->old_fd);
	if (executor_state->command->next)
		replace_fds(executor_state);
}

void	exec_command(t_executor executor_state, char **env)
{
	t_child_command	built_in;
	char			*command_path;
	char			**command_args;
	int				command_position;

	command_args = list_to_arr(executor_state.command->arg);
	built_in = is_child_command(command_args[0]);
	if (built_in.is_child_command)
		exit(built_in.handler(executor_state.command->arg, env));
	command_path = get_command_path(executor_state.command->arg->val, env);
	command_position = executor_state.command_position;
	executor_state.commands_paths[command_position] = command_path;
	executor_state.commands_args[command_position] = command_args;
	execve(command_path, command_args, env);
	handle_errors(command_args[0], env);
}
