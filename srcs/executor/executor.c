#include "executor.h"
#include <signal.h>
#include <termios.h>

/* Signal Handler for SIGINT */
int  code;
bool forked;
int  is_heredoc;

void sigintHandler(int sig_num)
{
	if (forked)
	{
		printf("forked\n");
		write(1, "\n", 1);
		rl_on_new_line();
	}
	else
	{
		write(1, "\n", 1);
		// rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
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

	code = 0;
	executor.env = (char ***) malloc(sizeof(char **));
	*executor.env = copy_env(env);
	ignctl();
	signal(SIGINT, sigintHandler);
	while (true)
	{
		executor.command_position = 0;
		forked = false;
		cmd = readline("bazsh$ ");
		add_history(cmd);
		lexer = new_lexer(cmd);
		parser = parser_new(lexer);
		executor.command = start_parser(parser);
		start_execution(&executor, env);
		free_all_memory(executor, parser);
		waitpids(executor.pids, executor.command_position);
	}
	free_double_pointer(*executor.env);
	return (0);
}