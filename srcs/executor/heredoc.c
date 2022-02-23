/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:38:52 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/23 13:33:59 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	heredoc_handler(int signum)
{
	signum = 0;
	write(1, "\n", 1);
	exit(10);
}

int	set_signals(int pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		set_status_code(0);
	else if (WEXITSTATUS(status) == 10)
	{
		set_status_code(1);
		return (0);
	}
	return (1);
}

void	write_to_file(char *delim, int fd)
{
	char	*line;

	while (true)
	{
		line = readline(">> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, delim))
		{
			break ;
		}
		write_line(line, fd);
	}
	close(fd);
	exit(1);
}

int	execute_heredoc(t_io *sequence, int file_num)
{
	int		fd;
	pid_t	pid;
	char	*file_name;
	char	*delim;

	file_name = ft_itoa(file_num);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	delim = ft_strdup(sequence->value);
	replace_sequence(sequence, file_name);
	free(file_name);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_handler);
		write_to_file(delim, fd);
		free(delim);
	}
	return (set_signals(pid));
}

int	handle_heredoc(t_executor *executor)
{
	t_io		*sequence;
	int			file_num;
	t_command	*command;

	command = executor->command;
	file_num = 0;
	while (command)
	{
		sequence = command->in_sequence;
		while (sequence)
		{
			if (sequence->type == IO_HEREDOC)
			{
				if (!execute_heredoc(sequence, file_num))
					return (0);
				file_num += 1;
			}
			sequence = sequence->next;
		}
		command = command->next;
	}
	return (1);
}
