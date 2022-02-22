/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:02:46 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:03:27 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	list_count(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	return (i);
}

void	write_line(const char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	replace_sequence(t_io *sequence,
			const char *value, enum io_type newtype)
{
	free(sequence->value);
	sequence->value = ft_strdup(value);
	sequence->type = IO_FILE;
}

int	get_var_index(const char *var_name, char **env)
{
	size_t	i;
	char	**tmpenv;

	i = 0;
	while (env[i])
	{
		tmpenv = ft_split(env[i], '=');
		if (ft_strcmp(tmpenv[0], var_name) == 0 && tmpenv[1])
			return (i);
		free_double_pointer(tmpenv);
		i += 1;
	}
	return (-1);
}
