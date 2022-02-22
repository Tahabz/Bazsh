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

	while (true)
	{
		line = readline(">> ");
		if (!line)
			break;
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
				if (WEXITSTATUS(status) == 1)
					set_status_code(0);
				else if (WEXITSTATUS(status) == 10)
				{
					set_status_code(1);
					return (0);
				}
			}
			sequence = sequence->next;
		}
		command = command->next;
	}
	return 1;
}