#include "executor.h"

void heredocHandler(int sig_num)
{
	write(1, "\n", 1);
	exit(10);
}

void write_to_file(char *delim, int file_numm, int fd)
{
	int   i;
	char *line;
	char *file_name;

	is_heredoc = 1;
	while (true)
	{
		line = readline(">>");
		if (!ft_strcmp(line, delim))
		{
			break;
		}
		write_line(line, fd);
	}
	// replace_sequence(sequence, file_name, IO_FILE);
	close(fd);
	exit(1);
}

int handle_heredoc(t_executor *executor)
{
	t_io      *sequence;
	int        file_num;
	t_command *command;
	int        status;
	int        ret;
	int        fd;

	command = executor->command;
	file_num = 0;
	while (command)
	{
		sequence = command->in_sequence;
		while (sequence)
		{
			if (sequence->type == IO_HEREDOC)
			{
				// CREATE THE FILE
				char *file_name = ft_itoa(file_num);
				fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				char *delim = ft_strdup(sequence->value);
				replace_sequence(sequence, file_name, IO_FILE);
				free(file_name);
				pid_t pid = fork();
				if (pid == 0)
				{
					signal(SIGINT, heredocHandler);
					write_to_file(delim, file_num, fd);
					free(delim);
				}
				signal(SIGINT, SIG_IGN);
				waitpid(pid, &status, 0);
				file_num += 1;
				if (WIFEXITED(status))
				{
					ret = WEXITSTATUS(status);
					if (ret == 10)
					{
						// REMOVE CREATED FILES
						return 0;
					}
				}
			}
			sequence = sequence->next;
		}
		command = command->next;
	}
	return 1;
}