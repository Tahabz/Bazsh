/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:04:42 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:06:59 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i++])
		;
	return (i);
}
