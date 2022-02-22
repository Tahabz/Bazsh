#include "executor.h"

void init_signals(void)
{
	ignctl();
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	set_status_code(0);
}

void set_status_code(int code)
{
	char *code_str;

	code_str = "0";
	if (code >= 0)
		code_str = ft_itoa(code);
	else if (WIFSIGNALED(g_status))
	{
		if (WTERMSIG(g_status) == SIGINT)
			code_str = ft_itoa(130);
		else if (WTERMSIG(g_status) == SIGQUIT)
			code_str = ft_itoa(131);
	}
	else
		code_str = ft_itoa(WEXITSTATUS(g_status));
	g_code = code_str;
}

void signalHandler(int signal)
{
	if (signal == SIGQUIT && g_forked)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
	}
	if (signal == SIGQUIT && !g_forked)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGINT && g_forked)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	if (signal == SIGINT && !g_forked)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		set_status_code(1);
	}
}

void ignctl(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		perror("tcgetattr() error");
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		perror("tcsetattr() error");
}