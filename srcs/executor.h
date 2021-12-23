#include "../srcs/parser.h"

typedef struct s_executor
{
	int    new_fd[2];
	int    old_fd[2];
	int    command_position;
	int    pids[1000];
	char  *commands_paths[1000];
	char **commands_args[1000];

	t_command *command;
} t_executor;

typedef struct s_file
{
	int   fd;
	char *error;
} t_file;