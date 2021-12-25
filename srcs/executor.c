#include "executor.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

bool ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	else if (c >= 'A' && c <= 'Z')
		return (true);
	else if (c == '_')
		return (true);
	return (false);
}

bool ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

bool ft_isnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i += 1;
	}
	return (true);
}

void ft_exit(t_arg *arg, char **env)
{
	arg = arg->next;
	if (!arg)
		exit(code);
	if (!ft_isnum(arg->val))
	{
		ft_putstr_fd("exit\bbazsh: exit: f: numeric argument required\n", 2);
		exit(255);
	}
	if (arg->next)
		ft_putstr_fd("exit\nbazsh: exit: too many arguments\n", 2);
	exit(atoi(arg->val));
}

bool arr_contain(char *arr, char c)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == c)
			return (true);
		i++;
	}
	return (false);
}

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

char arr_length(char **arr)
{
	int i;

	i = 0;

	while (arr[i++])
		;
	return (i);
}

char **push(char **arr, char *val)
{
	int    i;
	int    length;
	char **new_arr;

	length = arr_length(arr);
	new_arr = (char **) malloc((length + 1) * sizeof(char *));

	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i += 1;
	}
	new_arr[i] = ft_strdup(val);
	new_arr[i + 1] = NULL;
	free_double_pointer(arr);
	return (new_arr);
}

int get_var_index(const char *var_name, char **env)
{
	size_t i;
	char **tmpenv;

	i = 0;
	while (env[i])
	{
		tmpenv = ft_split(env[i], '=');
		if (ft_strcmp(tmpenv[0], var_name) == 0 && tmpenv[1])
			return (i);
		free_double_pointer(tmpenv);
		i += 1;
	}
	return (-1);
}

char *make_env_name(char *var_name, char *var_value)
{
	char *tmp;
	char *name;

	tmp = ft_strjoin(var_name, "=");
	name = ft_strjoin(tmp, var_value);
	free(tmp);
	return (name);
}

void set_env(char *var_name, char *var_value, char ***env)
{
	int   i;
	char *name;

	name = make_env_name(var_name, var_value);
	i = get_var_index(var_name, *env);
	if (i != -1)
		env[0][i] = ft_strdup(name);
	else
		*env = push(*env, name);
	free(name);
}

char *ft_getenv(const char *var_name, char **env)
{
	size_t i;
	char **tmpenv;
	char * val;

	i = 0;
	while (env[i])
	{
		tmpenv = ft_split(env[i], '=');
		if (!tmpenv[0])
		{
			free(tmpenv);
			break;
		}
		if (!ft_strcmp(tmpenv[0], var_name) && tmpenv[1])
		{
			val = ft_substr(env[i], ft_strlen(tmpenv[0]) + 1, ft_strlen(env[i]));
			free_double_pointer(tmpenv);
			return (val);
		}
		free_double_pointer(tmpenv);
		i += 1;
	}
	return (NULL);
}

bool is_not_empty_ident(char *str)
{
	return (arr_contain(str, '='));
}

bool is_empty_ident(char *str)
{
	return (true);
}

void print_2d_arr(char **arr, bool(callback)(char *))
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (callback(arr[i]))
			printf("%s\n", arr[i]);
		i += 1;
	}
}

void pwd(t_arg *arg, char **env)
{
	printf("%s\n", getcwd(*env, 100));
}

void env(t_arg *arg, char **env)
{
	print_2d_arr(env, is_not_empty_ident);
}

void echo(t_arg *arg, char **env)
{
	int i;
	int new_line;

	new_line = true;
	arg = arg->next;
	if (!ft_strcmp(arg->val, "-n"))
	{
		arg = arg->next;
		new_line = false;
	}
	while (arg)
	{
		printf("%s", arg->val);
		if (arg->next)
			printf(" ");
		arg = arg->next;
	}
	if (new_line)
		printf("\n");
}

void cd(t_arg *args, char ***env)
{
	char  arr[100];
	char *arg;

	if (!args)
		arg = ft_getenv("HOME", *env);
	else
		arg = ft_strdup(args->next->val);
	if (chdir(arg) == -1)
	{
		free(arg);
		return (perror("cd"));
	}
	free(arg);
	set_env("pwd", getcwd(arr, 100), env);
	// printf("pwd = %s\n", ft_getenv("pwd", *env));
}

bool is_ident(char *ident)
{
	int i;

	if (!ft_isalpha(ident[0]))
		return (false);
	i = 1;
	while (ident[i])
	{
		if (!ft_isalnum(ident[i]))
			return (false);
		i += 1;
	}
	return (true);
}

bool keys_cmp(char *str, char *key)
{
	char **key_value;
	char * str_key;
	int    is_matching;
	key_value = ft_split(str, '=');
	str_key = key_value[0];
	is_matching = str_match(key, str_key);
	free_double_pointer(key_value);
	return (is_matching);
}

bool arr_2d_contains(char **arr, char *str, bool(comparer)(char *, char *))
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (comparer(arr[i], str))
			return (true);
		i += 1;
	}
	return (false);
}

char **push_if_not_exists(char **arr, char *str)
{
	if (!arr_2d_contains(arr, str, keys_cmp))
		return (push(arr, str));
	return (arr);
}

void set_ident(char *arg, char ***env)
{
	char **var;
	char * val;

	var = ft_split(arg, '=');
	if (!*var || !is_ident(var[0]))
		ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
	else if (!arr_contain(arg, '='))
		*env = push_if_not_exists(*env, var[0]);
	else
	{
		val = ft_substr(arg, ft_strlen(var[0]) + 1, ft_strlen(arg));
		set_env(var[0], val, env);
		free(val);
	}
	free_double_pointer(var);
}

void export(t_arg *arg, char ***env)
{
	char **var;
	char * val;

	if (!arg)
		return print_2d_arr(*env, is_empty_ident);
	arg = arg->next;
	if (arg->val[0] == '=')
		return (ft_putstr_fd("not a valid identifier \n", STDERR_FILENO));
	while (arg)
	{
		if (!ft_strcmp(arg->val, ""))
			ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
		else
			set_ident(arg->val, env);
		arg = arg->next;
	}
}

int get_args_count(t_arg *arg)
{
	int i;

	i = 0;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	return (i);
}

char **args_to_arr(t_arg *arg)
{
	int    args_count;
	char **args;
	int    i;

	args_count = get_args_count(arg);
	args = (char **) malloc((args_count + 1) * sizeof(char *));
	i = 0;
	while (arg)
	{
		args[i] = arg->val;
		arg = arg->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char **arr_remove(char **arr, char *val)
{
	int    i;
	int    j;
	char **new_arr;
	char * var;
	char * var_val;

	var_val = ft_getenv(val, arr);
	if (!var_val)
		return (arr);
	new_arr = (char **) malloc(arr_length(arr) * sizeof(char *));
	i = 0;
	j = 0;
	var = make_env_name(val, var_val);
	free(var_val);
	while (arr[i])
	{
		if (ft_strcmp(arr[i], var))
		{
			new_arr[j] = ft_strdup(arr[i]);
			j += 1;
		}
		i += 1;
	}
	new_arr[j] = val;
	new_arr[j + 1] = NULL;
	free(var);
	free_double_pointer(arr);
	return (new_arr);
}

void unset(t_arg *arg, char ***env)
{
	int i;

	if (!arg)
		return;
	arg = arg->next;
	while (arg)
	{
		if (!is_ident(arg->val))
			ft_putstr_fd("not a valid identifier \n", STDERR_FILENO);
		else
		{
			*env = arr_remove(*env, arg->val);
			// printf("unset %s=%s\n", arg->val, ft_getenv(arg->val, *env));
		}
		arg = arg->next;
	}
}

char *join_path(char *str1, char *str2)
{
	char *tmp_path = ft_strjoin(str1, "/");
	char *joined_path = ft_strjoin(tmp_path, str2);
	free(tmp_path);
	return (joined_path);
}

char *get_command_path(char *command_name, char **env)
{
	char **paths;
	int    i;
	char * command_path;

	if (!*command_name)
		return "";
	if (command_name[0] == '/')
		return (command_name);
	char *path = ft_getenv("PATH", env);
	paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (paths[i])
	{
		command_path = join_path(paths[i], command_name);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		i += 1;
	}
	free_double_pointer(paths);
	return (command_path);
}

void waitpids(int pids[], size_t i)
{
	if (!*pids)
		return;
	while (i--)
	{
		int pid = waitpid(pids[i], &code, 0);
		if (pid == -1)
			perror("wait() error");
		else if (pid == 0)
		{
			printf("child is still running at");
		}
	}
}

void close_fd(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

void setup_pipes(t_command command, size_t position, int old_fd[], int new_fd[])
{
}

void dup_and_close(int fd[], int file_no)
{
	dup2(fd[file_no], file_no);
	close_fd(fd);
}

t_child_command is_child_command(char *command_name)
{
	if (!ft_strcmp(command_name, "pwd"))
		return (t_child_command){true, pwd};
	else if (!ft_strcmp(command_name, "echo"))
		return (t_child_command){true, echo};
	else if (!ft_strcmp(command_name, "env"))
		return (t_child_command){true, env};
	return (t_child_command){false, NULL};
}

void exec_command(t_executor executor_state, char **env)
{
	t_child_command built_in;
	char *          command_path;
	char **         command_args;
	int             command_position;

	command_args = args_to_arr(executor_state.command->arg);
	built_in = is_child_command(command_args[0]);
	if (built_in.is_child_command)
	{
		built_in.handler(executor_state.command->arg, env);
		exit(1);
	}
	command_path = get_command_path(executor_state.command->arg->val, env);
	command_position = executor_state.command_position;
	executor_state.commands_paths[command_position] = command_path;
	executor_state.commands_args[command_position] = command_args;
	if (execve(command_path, command_args, env) == -1)
	{
		perror("execve");
		exit(1);
	}
}

int get_last_fd(t_io *sequence, int(callback)(t_io *))
{
	int fd;

	while (sequence)
	{
		fd = callback(sequence);
		sequence = sequence->next;
	}
	return (fd);
}

int create_file(t_io *sequence)
{
	int fd;
	if (sequence->type == IO_FILE)
		fd = open(sequence->value,
		          O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		fd = open(sequence->value,
		          O_CREAT | O_APPEND | O_WRONLY, 0644);
	return (fd);
}

int open_file(t_io *sequence)
{
	int fd;

	fd = open(sequence->value, O_RDONLY, 0);
	if (fd == -1)
	{
		printf("file does not exist %s\n", sequence->value);
		exit(0);
	}
	return (fd);
}

void write_line(const char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void replace_sequence(t_io *sequence, const char *value, enum io_type newtype)
{
	free(sequence->value);
	sequence->value = ft_strdup(value);
	sequence->type = IO_FILE;
}

void transform_heredoc(t_io *sequence, int file_num)
{
	int   fd;
	int   i;
	char *line;
	char *file_name;

	file_name = ft_itoa(file_num);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (true)
	{
		line = readline(">>");
		if (!ft_strcmp(line, sequence->value))
			break;
		write_line(line, fd);
	}
	replace_sequence(sequence, file_name, IO_FILE);
	free(file_name);
	close(fd);
}

void handle_heredoc(t_command *command)
{
	t_io *sequence;
	int   file_num;

	file_num = 0;
	while (command)
	{
		sequence = command->in_sequence;
		while (sequence)
		{
			if (sequence->type == IO_HEREDOC)
			{
				transform_heredoc(sequence, file_num);
				file_num += 1;
			}
			sequence = sequence->next;
		}
		command = command->next;
	}
}

void exec_child_command(t_executor executor_state, char **env)
{
	int   fd;
	int   hfd[2];
	char *f = "";

	char **command_args = args_to_arr(executor_state.command->arg);
	if (!ft_strcmp(executor_state.command->arg->val, "exit"))
		ft_exit(executor_state.command->arg, env);
	if (executor_state.command->in_sequence)
	{
		fd = get_last_fd(executor_state.command->in_sequence, open_file);
		if (fd)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	else if (executor_state.command_position > 0)
		dup_and_close(executor_state.old_fd, STDIN_FILENO);
	if (executor_state.command->out_sequence && executor_state.command->out_sequence->type != IO_PIPE)
	{
		fd = get_last_fd(executor_state.command->out_sequence, create_file);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (executor_state.command->next)
		dup_and_close(executor_state.new_fd, STDOUT_FILENO);
	exec_command(executor_state, env);
}

t_parent_command is_parent_command(char *command_name)
{
	if (!ft_strcmp(command_name, "cd"))
		return (t_parent_command){true, cd};
	else if (!ft_strcmp(command_name, "export"))
		return (t_parent_command){true, export};
	else if (!ft_strcmp(command_name, "unset"))
		return (t_parent_command){true, unset};
	return (t_parent_command){false, NULL};
}

void handle_command(t_executor *executor_state, char ***env)
{
	t_parent_command command;

	command = is_parent_command(executor_state->command->arg->val);
	if (command.is_parent_command)
	{
		executor_state->command_position -= 1;
		return (command.handler(executor_state->command->arg, env));
	}
	else if (!ft_strcmp(executor_state->command->arg->val, "exit") && !executor_state->command->next)
		ft_exit(executor_state->command->arg, *env);
	if (executor_state->command->next)
		pipe(executor_state->new_fd);
	executor_state->pids[executor_state->command_position] = fork();
	if (executor_state->pids[executor_state->command_position] == 0)
		exec_child_command(*executor_state, *env);
	if (executor_state->command_position > 0)
		close_fd(executor_state->old_fd);
	if (executor_state->command->next)
	{
		executor_state->old_fd[0] = executor_state->new_fd[0];
		executor_state->old_fd[1] = executor_state->new_fd[1];
	}
}

char **copy_env(char **env)
{
	int    length;
	int    i;
	char **cpy_env;

	length = arr_length(env);
	i = 0;
	cpy_env = (char **) malloc((length) * sizeof(char *));

	while (env[i])
	{
		cpy_env[i] = ft_strdup(env[i]);
		i++;
	}
	cpy_env[i] = NULL;
	return (cpy_env);
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
	i = 0;
	while (executor.commands_args[i])
	{
		free_double_pointer(executor.commands_args[i]);
		i += 1;
	}
	free_double_pointer(*executor.env);
	delete_command(executor.command);
	free(executor.env);
}

int main(int ac, char **av, char **env)
{
	int        i = 0;
	t_lexer    lexer;
	t_parser * parser;
	t_executor executor_state;

	executor_state.env = (char ***) malloc(sizeof(char **));
	*executor_state.env = copy_env(env);
	lexer = new_lexer("cat < file > taha | export taha=baz | unset taha | echo -n watafiin al3awd | ls -la | wc -l");
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
	delete_parser(parser);
	delete_executor(executor_state);
	waitpids(executor_state.pids, executor_state.command_position);
	return (0);
}