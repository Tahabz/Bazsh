#include "../srcs/parser.h"

int code = 0;

typedef struct s_executor
{
	int        new_fd[2];
	int        old_fd[2];
	int        command_position;
	int        pids[1000];
	char *     commands_paths[1000];
	char **    commands_args[1000];
	t_command *command;
	char ***   env;
} t_executor;

typedef struct s_parent_command
{
	bool is_parent_command;
	void (*handler)(t_arg *, char ***);
} t_parent_command;

typedef struct t_child_command
{
	bool is_child_command;
	void (*handler)(t_arg *, char **);
} t_child_command;
typedef struct s_file
{
	int   fd;
	char *error;
} t_file;