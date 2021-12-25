#include "executor.h"

int code;

void start_execution(t_executor *executor, char **env)
{
	handle_heredoc(executor->command);
	executor->command_position = 0;
	while (executor->command)
	{
		handle_command(executor, executor->env);
		executor->command_position += 1;
		executor->command = executor->command->next;
	}
}

int main(int ac, char **av, char **env)
{
	char *     cmd;
	t_lexer    lexer;
	t_parser * parser;
	t_executor executor;
	int        i = 0;

	code = 0;
	executor.env = (char ***) malloc(sizeof(char **));
	*executor.env = copy_env(env);
	while (true)
	{
		cmd = readline("bazsh$ ");
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