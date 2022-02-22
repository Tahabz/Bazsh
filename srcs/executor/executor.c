#include "executor.h"
#include <signal.h>
#include <termios.h>

/* Signal Handler for SIGINT */
int   status;
bool  forked;
char *g_code;

void set_status_code(int code)
{
	char *code_str;

	code_str = "0";
	if (code >= 0)
		code_str = ft_itoa(code);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			code_str = ft_itoa(130);
		else if (WTERMSIG(status) == SIGQUIT)
			code_str = ft_itoa(131);
	}
	else
		code_str = ft_itoa(WEXITSTATUS(status));
	g_code = code_str;
}

void signalHandler(int signal)
{
	if (signal == SIGQUIT && forked)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
	}
	if (signal == SIGQUIT && !forked)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGINT && forked)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	if (signal == SIGINT && !forked)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		set_status_code(1);
	}
}

void start_execution(t_executor *executor, char **env)
{
	executor->command_position = 0;
	if (!handle_heredoc(executor))
		return;
	while (executor->command)
	{
		handle_command(executor, executor->env);
		executor->command_position += 1;
		executor->command = executor->command->next;
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

int main(int ac, char **av, char **env)
{
	char      *cmd;
	t_lexer    lexer;
	t_parser  *parser;
	t_executor executor;
	int        i = 0;

	status = 0;
	executor.env = (char ***) malloc(sizeof(char **));
	*executor.env = copy_env(env);
	ignctl();
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	set_status_code(0);
	while (true)
	{
		executor.command_position = 0;
		forked = false;
		cmd = readline("bazsh$ ");
		if (cmd)
		{
			add_history(cmd);
			lexer = new_lexer(cmd);
			parser = parser_new(lexer);
			executor.command = start_parser(parser);
			start_execution(&executor, env);
			free_all_memory(executor, parser);
			waitpids(executor.pids, executor.command_position);
		}
		else
			exit(atoi(g_code));
	}
	free_double_pointer(*executor.env);
	return (0);
}