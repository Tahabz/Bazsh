/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:04:51 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:05:56 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR_TOOLS_H
# define ARR_TOOLS_H

# include "../executor/executor.h"

bool	arr_2d_contains(char **arr, char *str, bool(comparer)(char *, char *));
bool	arr_contains(char *arr, char c);
char	arr_length(char **arr);
char	**arr_remove(char **arr, char *val);
char	**list_to_arr(t_arg *arg);
char	**push(char **arr, char *val);
char	**push_if_not_exists(char **arr, char *str);
void	print_2d_arr(char **arr, bool(callback)(char *));
#endif
