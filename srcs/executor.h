#include "../srcs/parser.h"

typedef struct s_executor
{
	int        new_fd[2];
	int        old_fd[2];
	int        command_position;
	int        pids[1000];
	t_command *command;
} t_executor;
