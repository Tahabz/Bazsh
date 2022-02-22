#include "executor.h"
/* Signal Handler for SIGINT */
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

int main(int ac, char **av, char **env)
{
	char      *cmd;
	t_lexer    lexer;
	t_parser  *parser;
	t_executor executor;
	int        i = 0;

	g_status = 0;
	executor.env = (char ***) malloc(sizeof(char **));
	*executor.env = copy_env(env);
	ignctl();
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	set_status_code(0);
	while (true)
	{
		executor.command_position = 0;
		g_forked = false;
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