
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

t_command init_commands()
{
	char **args;

	args = malloc(sizeof(char *));

	args[0] = ft_strdup("lexer.c");

	char **args2;

	args2 = malloc(sizeof(char *));

	args2[0] = ft_strdup("#include");

	t_command command = {
	    .name = "cat",
	    .args = args,
	    .out = (t_io){.type = IO_PIPE,
	                  .value = NULL},
	};

	t_command *command2 = malloc(sizeof(t_command));
	command2->name = "grep";
	command2->args = args2,
	command2->in = (t_io){.type = IO_PIPE,
	                      .value = NULL};

	command.next = command2;

	return command;
}

int main(int ac, char **av, char **env)
{
	t_command command;

	command = init_commands();
	printf("name = %s, args = %s, in = %d\n", command.name, command.args[0], command.in.type);
	printf("name = %s, args = %s, in = %d", command.next->name, command.next->args[0], command.next->in.type);

	return 0;
	// int fd[2];
	// int pid1;
	// int pid2;
	// // char *args[] = {"cat", "lexer.c", NULL};

	// if (pipe(fd) == -1)
	// 	return -1;
	// pid1 = fork();
	// if (pid1 == 0)
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execve("/usr/bin/cat", (char *[3]){"cat", "lexer.c", NULL}, env);
	// }

	// pid2 = fork();
	// if (pid2 == 0)
	// {
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execve("/usr/bin/grep", (char *[3]){"grep", "lexer", NULL}, env);
	// }

	// close(fd[0]);
	// close(fd[1]);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
}