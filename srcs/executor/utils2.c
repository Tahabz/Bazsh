/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:03:34 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:04:17 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

bool	keys_cmp(char *str, char *key)
{
	char	**key_value;
	char	*str_key;
	int		is_matching;

	key_value = ft_split(str, '=');
	str_key = key_value[0];
	is_matching = str_match(key, str_key);
	free_double_pointer(key_value);
	return (is_matching);
}

void	waitpids(int pids[], size_t i)
{
	int	j;
	int	pid;

	j = i;
	if (!*pids)
		return ;
	while (i--)
	{
		pid = waitpid(pids[i], &g_signal.status, 0);
		if (pid == -1)
		{
			ft_putstr_fd("error in main\n", 2);
			perror("wait() error");
		}
		else if (pid == 0)
		{
			printf("child is still running at");
		}
	}
	if (j != 0)
		set_status_code(-1);
}
