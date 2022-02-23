/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:01:45 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/23 15:48:19 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	init_signals(void)
{
	ignctl();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	set_status_code(0);
}

void	set_status_code(int code)
{
	char	*code_str;

	code_str = "0";
	if (code >= 0)
		code_str = ft_itoa(code);
	else if (WIFSIGNALED(g_signal.status))
	{
		if (WTERMSIG(g_signal.status) == SIGINT)
			code_str = ft_itoa(130);
		else if (WTERMSIG(g_signal.status) == SIGQUIT)
			code_str = ft_itoa(131);
	}
	else
		code_str = ft_itoa(WEXITSTATUS(g_signal.status));
	g_signal.code = code_str;
}

void	signal_handler(int signal)
{
	if (signal == SIGQUIT && g_signal.forked)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
	}
	if (signal == SIGQUIT && !g_signal.forked)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGINT && g_signal.forked)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	if (signal == SIGINT && !g_signal.forked)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		set_status_code(1);
	}
}

void	ignctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		perror("tcgetattr() error");
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		perror("tcsetattr() error");
}

void	expand_signal(char **cmd_args)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd_args[i])
	{
		if (str_match(cmd_args[i], "?"))
		{
			tmp = cmd_args[i];
			cmd_args[i] = ft_strdup(g_signal.code);
			free(tmp);
		}
		i++;
	}
}
