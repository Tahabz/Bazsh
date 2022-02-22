/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:42:05 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 20:31:58 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	print_args(t_arg *arg)
{
	while (arg)
	{
		printf("%s", arg->val);
		if (arg->next)
			printf(" ");
		arg = arg->next;
	}
}

int	echo(t_arg *arg, char **env)
{
	int		i;
	bool	new_line;

	new_line = true;
	arg = arg->next;
	if (!arg)
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp(arg->val, "-n"))
	{
		arg = arg->next;
		new_line = false;
	}
	else if (!ft_strcmp(arg->val, "?"))
	{
		arg = arg->next;
		ft_putstr_fd(g_signal.code, 1);
		fflush(stderr);
	}
	print_args(arg);
	if (new_line)
		printf("\n");
	return (0);
}
