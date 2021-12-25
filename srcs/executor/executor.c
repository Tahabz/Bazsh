#include "executor.h"

int code;

void start_executor(char *cmd, char **env)
{
	int        i = 0;
	t_lexer    lexer;
	t_parser * parser;
	t_executor executor_state;

	code = 0;
	executor_state.env = (char ***) malloc(sizeof(char **));
	*executor_state.env = copy_env(env);
	lexer = new_lexer(cmd);
	parser = parser_new(lexer);
	executor_state.command = start_parser(parser);
	handle_heredoc(executor_state.command);
	executor_state.command_position = 0;
	while (executor_state.command)
	{
		handle_command(&executor_state, executor_state.env);
		executor_state.command_position += 1;
		executor_state.command = executor_state.command->next;
	}
	free_all_memory(executor_state, parser);
	waitpids(executor_state.pids, executor_state.command_position);
}

int main(int ac, char **av, char **env)
{
	char *cmd;

	while (true)
	{
		cmd = readline("bazsh$ ");
		start_executor(cmd, env);
	}
	return (0);
}