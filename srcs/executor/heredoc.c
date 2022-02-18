#include "executor.h"

void transform_heredoc(t_io *sequence, int file_num)
{
	int   fd;
	int   i;
	char *line;
	char *file_name;

	is_heredoc = 1;
	file_name = ft_itoa(file_num);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (true)
	{
		if (get_next_line(0, &line) < 0)
			exit(0);
		if (!ft_strcmp(line, sequence->value))
			break;
		write_line(line, fd);
	}
	replace_sequence(sequence, file_name, IO_FILE);
	free(file_name);
	close(fd);
	is_heredoc = 0;
}

void handle_heredoc(t_executor *executor)
{
	t_io      *sequence;
	int        file_num;
	t_command *command;

	command = executor->command;
	file_num = 0;
	while (command)
	{
		sequence = command->in_sequence;
		while (sequence)
		{
			if (sequence->type == IO_HEREDOC)
			{
				pid_t pid = fork();
				if (pid == 0)
					transform_heredoc(sequence, file_num);
				file_num += 1;
				pid = waitpid(pid, &code, 0);
				if (pid == -1)
				{
					ft_putstr_fd("error in heredoc\n", 2);
					perror("wait() error");
				}
				else if (pid == 0)
				{
					printf("child is still running at");
				}
			}
			sequence = sequence->next;
		}
		command = command->next;
	}
}