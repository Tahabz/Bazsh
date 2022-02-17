#include "executor.h"

void free_double_pointer(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void delete_executor(t_executor executor)
{
	int i;

	i = 0;
	while (executor.commands_paths[i])
	{
		free(executor.commands_paths[i]);
		i += 1;
	}
	// i = 0;
	// while (executor.commands_args[i])
	// {
	// 	free_double_pointer(executor.commands_args[i]);
	// 	i += 1;
	// }
}

void free_all_memory(t_executor executor, t_parser *parser)
{
	delete_executor(executor);
	delete_parser(parser);
	delete_command(executor.command);
}