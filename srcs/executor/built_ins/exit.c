/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:44:15 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/23 16:23:16 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	ft_exit(t_arg *arg, char **env)
{
	(void) env;
	arg = arg->next;
	if (!arg)
		exit(g_signal.status);
	if (!ft_isnum(arg->val))
	{
		ft_putstr_fd("exit\bbazsh: exit: f: numeric argument required\n", 2);
		exit(255);
	}
	if (arg->next)
	{
		ft_putstr_fd("exit\nbazsh: exit: too many arguments\n", 2);
		g_signal.code = ft_itoa(1);
		return ;
	}
	exit(atoi(arg->val));
}
