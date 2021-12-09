#include "../srcs/parser.h"
#include "lexer.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int ac, char **av, char **env)
{
	const t_lexer lexer = new_lexer("/bin/cat srcs/executor.c | /usr/bin/grep main");
	t_parser *    parser = parser_new(lexer);
	t_command *   command = start_parser(parser);

	int fd[2];
	int fdx[2];
	int pid1;
	int pid2;
	int pidx;

	int arr[2];
	if (pipe(fdx) == -1)
		return -1;
	int i = 0;
	while (command)
	{
		pidx = fork();
		arr[i] = pidx;
		i++;
		if (pidx == 0)
		{
			if (command->out_sequence && command->out_sequence->type == IO_PIPE)
			{
				dup2(fdx[1], STDOUT_FILENO);
			}
			if (!command->in_sequence && !command->out_sequence)
			{
				dup2(fdx[0], STDIN_FILENO);
			}
			close(fdx[1]);
			close(fdx[0]);
			if (execve(command->arg->val, (char *[3]){command->arg->val, command->arg->next->val, NULL}, env) == -1)
			{
				perror("execve");
				exit(1);
			}
		}

		command = command->next;
	}
	close(fdx[1]);
	close(fdx[0]);
	waitpid(arr[0], NULL, 0);
	waitpid(arr[1], NULL, 0);
	// if (pipe(fd) == -1)
	// 	return -1;
	// pid1 = fork();
	// if (pid1 == 0)
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execve("/bin/cat", (char *[3]){"cat", "srcs/executor.c", NULL}, env);
	// }

	// pid2 = fork();
	// if (pid2 == 0)
	// {
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execve("/usr/bin/grep", (char *[3]){"grep", "main", NULL}, env);
	// }

	// pid2 = fork();
	// if (pid2 == 0)
	// {

	// }

	close(fdx[0]);
	close(fdx[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}