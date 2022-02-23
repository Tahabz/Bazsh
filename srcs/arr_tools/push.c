/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:05:04 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:05:07 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr_tools.h"

char	**push_if_not_exists(char **arr, char *str)
{
	if (!arr_2d_contains(arr, str, keys_cmp))
		return (push(arr, str));
	return (arr);
}

char	**push(char **arr, char *val)
{
	int		i;
	int		length;
	char	**new_arr;

	length = arr_length(arr);
	new_arr = (char **) malloc((length + 1) * sizeof(char *));
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i += 1;
	}
	new_arr[i] = ft_strdup(val);
	new_arr[i + 1] = NULL;
	free_double_pointer(arr);
	return (new_arr);
}
