/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:42:35 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 16:24:05 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

char	**copy_env(char **env)
{
	int		length;
	int		i;
	char	**cpy_env;

	length = arr_length(env);
	i = 0;
	cpy_env = (char **) malloc((length) * sizeof(char *));
	while (env[i])
	{
		cpy_env[i] = ft_strdup(env[i]);
		i++;
	}
	cpy_env[i] = NULL;
	return (cpy_env);
}

char	*make_env_name(char *var_name, char *var_value)
{
	char	*tmp;
	char	*name;

	tmp = ft_strjoin(var_name, "=");
	name = ft_strjoin(tmp, var_value);
	free(tmp);
	return (name);
}

void	set_env(char *var_name, char *var_value, char ***env)
{
	int		i;
	char	*name;

	name = make_env_name(var_name, var_value);
	i = get_var_index(var_name, *env);
	if (i != -1)
		env[0][i] = ft_strdup(name);
	else
		*env = push(*env, name);
	free(name);
}

char	*ft_getenv(const char *var_name, char **env)
{
	size_t		i;
	char		**tmpenv;
	char		*val;

	i = 0;
	while (env[i])
	{
		tmpenv = ft_split(env[i], '=');
		if (!tmpenv[0])
		{
			free(tmpenv);
			break ;
		}
		if (!ft_strcmp(tmpenv[0], var_name) && tmpenv[1])
		{
			val = ft_substr(env[i], ft_strlen(tmpenv[0]) + 1,
						ft_strlen(env[i]));
			free_double_pointer(tmpenv);
			return (val);
		}
		free_double_pointer(tmpenv);
		i += 1;
	}
	return (NULL);
}

int	env(t_arg *arg, char **env)
{
	print_2d_arr(env, is_not_empty_ident);
	return (0);
}
