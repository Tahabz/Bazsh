/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_contains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:04:39 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:06:50 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr_tools.h"

bool	arr_contains(char *arr, char c)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	arr_2d_contains(char **arr, char *str, bool(comparer)(char *, char *))
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (comparer(arr[i], str))
			return (true);
		i += 1;
	}
	return (false);
}
