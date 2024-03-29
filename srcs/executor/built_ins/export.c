/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:44:29 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/23 18:57:07 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

bool	is_ident(char *ident)
{
	int	i;

	if (!ft_isalpha(ident[0]))
		return (false);
	i = 1;
	while (ident[i])
	{
		if (!ft_isalnum(ident[i]))
			return (false);
		i += 1;
	}
	return (true);
}

bool	is_not_empty_ident(char *str)
{
	return (arr_contains(str, '='));
}

bool	is_empty_ident(char *str)
{
	str = NULL;
	printf("declare -x ");
	return (true);
}

void	set_ident(char *arg, char ***env)
{
	char	**var;
	char	*val;

	var = ft_split(arg, '=');
	if (!*var || !is_ident(var[0]))
		ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
	else if (!arr_contains(arg, '='))
		*env = push_if_not_exists(*env, var[0]);
	else
	{
		val = ft_substr(arg, ft_strlen(var[0]) + 1, ft_strlen(arg));
		set_env(var[0], val, env);
		free(val);
	}
	free_double_pointer(var);
}

int	export(t_arg *arg, char ***env)
{
	if (!arg->next)
	{
		print_2d_arr(*env, is_empty_ident);
		return (0);
	}
	arg = arg->next;
	if (arg->val[0] == '=')
	{
		ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
		return (1);
	}
	while (arg)
	{
		if (!ft_strcmp(arg->val, ""))
			ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
		else
			set_ident(arg->val, env);
		arg = arg->next;
	}
	return (0);
}
