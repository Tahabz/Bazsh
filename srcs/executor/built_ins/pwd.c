/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:45:24 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/23 16:03:04 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	pwd(t_arg *arg, char **env)
{
	(void) arg;
	(void) env;
	printf("%s\n", getcwd(*env, 100));
	return (0);
}
