#include "../srcs/parser.h"
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

void closepipes(int *pipes[2])
{
	int i = 100;
	while (i)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i--;
	}
}

int main(int ac, char **av, char **env)
{
	const t_lexer lexer = new_lexer("/bin/cat srcs/executor.c | /usr/bin/grep main | /usr/bin/wc -l");
	t_parser     *parser = parser_new(lexer);
	t_command    *command = start_parser(parser);

	// int fd[1024][2];
	pid_t pid;
	int   old_fd[2];
	int   new_fd[2];
	int   i;

	i = 0;
	while (command)
	{
		if (command->next)
			pipe(new_fd);
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
			{
				dup2(old_fd[0], STDIN_FILENO);
				close(old_fd[0]);
				close(old_fd[1]);
			}
			if (command->next)
			{
				close(new_fd[0]);
				dup2(new_fd[1], STDOUT_FILENO);
				close(new_fd[1]);
			}
			exec_command(command, env);
		}
		if (i > 0)
		{
			close(old_fd[0]);
			close(old_fd[1]);
		}
		if (command->next)
		{
			old_fd[0] = new_fd[0];
			old_fd[1] = new_fd[1];
		}
		i++;
		command = command->next;
	}

	if (i > 1)
	{
		close(old_fd[0]);
		close(old_fd[1]);
	}

	return 0;
}