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

int main(int ac, char **av, char **env)
{
	const t_lexer lexer = new_lexer("/bin/cat srcs/executor.c | /usr/bin/grep main | /usr/bin/wc -l");
	t_parser *    parser = parser_new(lexer);
	t_command *   command = start_parser(parser);

	int fd[2];
	int pid;
	int tfd;

	while (command)
	{
		if (pipe(fd) == -1)
			return -1;
		pid = fork();
		if (pid == 0)
		{
			dup2(tfd, STDIN_FILENO);
			if (command->next)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			exec_command(command, env);
		}
		wait(NULL);
		close(fd[1]);
		tfd = fd[0];
		command = command->next;
	}
}