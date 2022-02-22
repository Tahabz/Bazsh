/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:36:00 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 20:37:00 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	get_last_fd(t_io *sequence, int callback (t_io *))
{
	int	fd;

	while (sequence)
	{
		fd = callback(sequence);
		sequence = sequence->next;
	}
	return (fd);
}

int	create_file(t_io *sequence)
{
	int	fd;

	if (sequence->type == IO_FILE)
		fd = open(sequence->value,
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		fd = open(sequence->value,
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	return (fd);
}

int	open_file(t_io *sequence)
{
	int	fd;

	fd = open(sequence->value, O_RDONLY, 0);
	if (fd == -1)
	{
		printf("file does not exist %s\n", sequence->value);
		exit(0);
	}
	return (fd);
}
