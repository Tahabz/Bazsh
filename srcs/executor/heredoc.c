#include "executor.h"

void transform_heredoc(t_io *sequence, int file_num)
{
	int   fd;
	int   i;
	char *line;
	char *file_name;

	file_name = ft_itoa(file_num);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (true)
	{
		line = readline(">>");
		if (!ft_strcmp(line, sequence->value))
			break;
		write_line(line, fd);
	}
	replace_sequence(sequence, file_name, IO_FILE);
	free(file_name);
	close(fd);
}

void handle_heredoc(t_command *command)
{
	t_io *sequence;
	int   file_num;

	file_num = 0;
	while (command)
	{
		sequence = command->in_sequence;
		while (sequence)
		{
			if (sequence->type == IO_HEREDOC)
			{
				transform_heredoc(sequence, file_num);
				file_num += 1;
			}
			sequence = sequence->next;
		}
		command = command->next;
	}
}