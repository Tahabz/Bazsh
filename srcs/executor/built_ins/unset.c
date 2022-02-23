/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:45:44 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/23 16:57:12 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	unset(t_arg *arg, char ***env)
{
	if (!arg)
		return (0);
	arg = arg->next;
	while (arg)
	{
		if (!is_ident(arg->val))
		{
			ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
			return (2);
		}
		else
			*env = arr_remove(*env, arg->val);
		arg = arg->next;
	}
	return (0);
}
