/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:04:45 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/23 13:27:42 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr_tools.h"

char	**dup_arr(char **arr, char *var, char *val)
{
	int		i;
	int		j;
	char	**new_arr;

	j = 0;
	i = 0;
	new_arr = (char **) malloc(arr_length(arr) * sizeof(char *));
	while (arr[i])
	{
		if (ft_strcmp(arr[i], var))
		{
			new_arr[j] = ft_strdup(arr[i]);
			j += 1;
		}
		i += 1;
	}
	new_arr[j] = val;
	new_arr[j + 1] = NULL;
	return (new_arr);
}

char	**arr_remove(char **arr, char *val)
{
	char	**new_arr;
	char	*var;
	char	*var_val;

	var_val = ft_getenv(val, arr);
	if (!var_val)
		return (arr);
	var = make_env_name(val, var_val);
	free(var_val);
	new_arr = dup_arr(arr, var, val);
	free(var);
	free_double_pointer(arr);
	return (new_arr);
}
