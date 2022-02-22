#include "executor.h"

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

void read_and_execute(t_executor *executor, char **env)
{
	char     *cmd;
	t_lexer   lexer;
	t_parser *parser;

	while (true)
	{
		g_forked = false;
		cmd = readline("bazsh$ ");
		if (cmd)
		{
			add_history(cmd);
			lexer = new_lexer(cmd);
			parser = parser_new(lexer);
			executor->command = start_parser(parser);
			start_execution(executor, env);
			free_all_memory(*executor, parser);
			waitpids(executor->pids, executor->command_position);
		}
		else
			exit(atoi(g_code));
	}
}

int main(int ac, char **av, char **env)
{
	t_executor executor;

	g_status = 0;
	executor.env = (char ***) malloc(sizeof(char **));
	*executor.env = copy_env(env);
	init_signals();
	read_and_execute(&executor, env);
	free_double_pointer(*executor.env);
	return (0);
}