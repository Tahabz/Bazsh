#include "executor.h"
#include "lexer.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int get_args_count(t_arg *arg)
{
	int i;

	i = 0;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	return (i);
}

char **args_to_arr(t_arg *arg)
{
	int    args_count;
	char **args;
	int    i;

	args_count = get_args_count(arg);
	args = (char **) malloc((args_count + 1) * sizeof(char *));
	i = 0;
	while (arg)
	{
		args[i] = arg->val;
		arg = arg->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char *join_path(char *str1, char *str2)
{
	char *tmp_path = ft_strjoin(str1, "/");
	char *joined_path = ft_strjoin(tmp_path, str2);
	free(tmp_path);
	return (joined_path);
}

char *get_command_path(char *command_name)
{
	char **paths;
	int    i;
	char  *command_path;

	command_path = NULL;
	char *x = getenv("PATH");
	printf("PATH IS = %s", x);
	paths = ft_split(x, ':');
	i = 0;
	while (paths[i])
	{
		command_path = join_path(paths[i], command_name);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		i++;
	}
	return (command_path);
}

void waitpids(int pids[], size_t i)
{
	while (i--)
	{
		int pid = waitpid(pids[i], NULL, 0);
		if (pid == -1)
			perror("wait() error");
		else if (pid == 0)
		{
			printf("child is still running at");
		}
	}
}

void close_fd(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

void setup_pipes(t_command command, size_t position, int old_fd[], int new_fd[])
{
}

void dup_and_close(int fd[], int file_no)
{
	dup2(fd[file_no], file_no);
	close_fd(fd);
}

void exec_command(t_command *command, char **env)
{
	char **command_args = args_to_arr(command->arg);
	if (execve(command->arg->val, command_args, env) == -1)
	{
		perror("execve");
		exit(1);
	}
	free(command_args);
}

void exec_child_command(t_executor executor_state, char **env)
{
	if (executor_state.command_position > 0)
		dup_and_close(executor_state.old_fd, STDIN_FILENO);
	if (executor_state.command->next)
		dup_and_close(executor_state.new_fd, STDOUT_FILENO);
	exec_command(executor_state.command, env);
}

int main(int ac, char **av, char **env)
{
	const t_lexer lexer = new_lexer("/bin/ls | /bin/cat | /usr/bin/wc -l");
	t_parser     *parser = parser_new(lexer);
	t_executor    executor_state;
	executor_state.command = start_parser(parser);

	executor_state.command_position = 0;
	while (executor_state.command)
	{
		if (executor_state.command->next)
			pipe(executor_state.new_fd);
		executor_state.pids[executor_state.command_position] = fork();
		if (executor_state.pids[executor_state.command_position] == 0)
			exec_child_command(executor_state, env);
		if (executor_state.command_position > 0)
			close_fd(executor_state.old_fd);
		if (executor_state.command->next)
		{
			executor_state.old_fd[0] = executor_state.new_fd[0];
			executor_state.old_fd[1] = executor_state.new_fd[1];
		}
		executor_state.command_position += 1;
		executor_state.command = executor_state.command->next;
	}
	waitpids(executor_state.pids, executor_state.command_position);
	return 0;
}