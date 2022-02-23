/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:35:14 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 20:35:15 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_fd(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

void	dup_and_close(int fd[], int file_no)
{
	dup2(fd[file_no], file_no);
	close_fd(fd);
}
