#include "executor.h"

extern bool forked;

void exec_child_command(t_executor executor_state, char **env)
{
	int    fd;
	int    hfd[2];
	char  *f = "";
	char **command_args = list_to_arr(executor_state.command->arg);
	if (!ft_strcmp(executor_state.command->arg->val, "exit"))
		ft_exit(executor_state.command->arg, env);
	if (executor_state.command->in_sequence)
	{
		fd = get_last_fd(executor_state.command->in_sequence, open_file);
		if (fd)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	else if (executor_state.command_position > 0)
		dup_and_close(executor_state.old_fd, STDIN_FILENO);
	if (executor_state.command->out_sequence && executor_state.command->out_sequence->type != IO_PIPE)
	{
		fd = get_last_fd(executor_state.command->out_sequence, create_file);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (executor_state.command->next)
		dup_and_close(executor_state.new_fd, STDOUT_FILENO);
	exec_command(executor_state, env);
}

void handle_command(t_executor *executor_state, char ***env)
{
	t_parent_command command;

	if (!executor_state->command->arg)
	{
		executor_state->command_position -= 1;
		return;
	}
	command = is_parent_command(executor_state->command->arg->val);
	if (command.is_parent_command)
	{
		executor_state->command_position -= 1;
		update_status_code(command.handler(executor_state->command->arg, env));
		return;
	}
	else if (!ft_strcmp(executor_state->command->arg->val, "exit") && !executor_state->command->next)
		ft_exit(executor_state->command->arg, *env);
	if (executor_state->command->next)
		pipe(executor_state->new_fd);
	forked = true;
	executor_state->pids[executor_state->command_position] = fork();
	if (executor_state->pids[executor_state->command_position] == 0)
		exec_child_command(*executor_state, *env);
	if (executor_state->command_position > 0)
		close_fd(executor_state->old_fd);
	if (executor_state->command->next)
	{
		executor_state->old_fd[0] = executor_state->new_fd[0];
		executor_state->old_fd[1] = executor_state->new_fd[1];
	}
}

void exec_command(t_executor executor_state, char **env)
{
	t_child_command built_in;
	char           *command_path;
	char          **command_args;
	int             command_position;

	command_args = list_to_arr(executor_state.command->arg);
	built_in = is_child_command(command_args[0]);
	if (built_in.is_child_command)
	{
		built_in.handler(executor_state.command->arg, env);
		exit(1);
	}
	command_path = get_command_path(executor_state.command->arg->val, env);
	command_position = executor_state.command_position;
	executor_state.commands_paths[command_position] = command_path;
	executor_state.commands_args[command_position] = command_args;
	if (execve(command_path, command_args, env) == -1)
	{
		perror("execve");
		exit(1);
	}
}

t_child_command is_child_command(char *command_name)
{
	if (!ft_strcmp(command_name, "pwd"))
		return (t_child_command){true, pwd};
	else if (!ft_strcmp(command_name, "echo"))
		return (t_child_command){true, echo};
	else if (!ft_strcmp(command_name, "env"))
		return (t_child_command){true, env};
	return (t_child_command){false, NULL};
}

t_parent_command is_parent_command(char *command_name)
{
	if (!ft_strcmp(command_name, "cd"))
		return (t_parent_command){true, cd};
	else if (!ft_strcmp(command_name, "export"))
		return (t_parent_command){true, export};
	else if (!ft_strcmp(command_name, "unset"))
		return (t_parent_command){true, unset};
	return (t_parent_command){false, NULL};
}