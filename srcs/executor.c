#include "executor.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

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

char *join_path(char *str1, char *str2)
{
	char *tmp_path = ft_strjoin(str1, "/");
	char *joined_path = ft_strjoin(tmp_path, str2);
	free(tmp_path);
	return (joined_path);
}

char *ft_getenv(const char *var_name, char **env)
{
	size_t i;
	char **tmpenv;

	i = 0;
	while (env[i])
	{
		tmpenv = ft_split(env[i], '=');
		if (ft_strcmp(tmpenv[0], var_name) == 0 && tmpenv[1])
			return tmpenv[1];
		i++;
	}
	return (NULL);
}

char *get_command_path(char *command_name, char **env)
{
	char **paths;
	int    i;
	char  *command_path;

	if (!*command_name)
		return "";
	if (command_name[0] == '/')
		return (command_name);
	char *path = ft_getenv("PATH", env);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		command_path = join_path(paths[i], command_name);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		i++;
	}
	return (command_path);
}

void waitpids(int pids[], size_t i)
{
	while (i--)
	{
		int pid = waitpid(pids[i], NULL, 0);
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

void exec_command(t_command *command, char **env)
{
	char **command_args = args_to_arr(command->arg);
	char  *command_path = get_command_path(command->arg->val, env);
	if (execve(command_path, command_args, env) == -1)
	{
		perror("execve");
		exit(1);
	}
	free(command_args);
}

int create_last_file(t_io *sequence)
{
	int fd;
	while (sequence->next)
	{
		creat(sequence->value, 0644);
		sequence = sequence->next;
	}
	fd = creat(sequence->value, 0644);
	return (fd);
}

void write_line(const char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int open_last_file(t_io *sequence)
{
	int   fd;
	char *f;
	int   hfd[2];
	int   tfd;

	tfd = dup(STDIN_FILENO);
	while (sequence)
	{
		if (sequence->type == IO_HEREDOC)
		{
			pipe(hfd);
			f = readline("");
			while (ft_strcmp(f, sequence->value))
			{
				write_line(f, hfd[1]);
				f = readline("");
			}
			dup_and_close(hfd, STDIN_FILENO);
			dup2(tfd, STDIN_FILENO);
			close(tfd);
			if (!sequence->next)
				return 0;
		}
		if (!sequence->next)
			break;
		sequence = sequence->next;
	}
	fd = open(sequence->value, O_RDONLY, 0);
	return (fd);
}

void exec_child_command(t_executor executor_state, char **env)
{
	int   fd;
	int   hfd[2];
	char *f = "";

	if (executor_state.command->in_sequence)
	{
		fd = open_last_file(executor_state.command->in_sequence);
		if (fd)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	else if (executor_state.command_position > 0)
		dup_and_close(executor_state.old_fd, STDIN_FILENO);
	if (executor_state.command->out_sequence && executor_state.command->out_sequence->type == IO_FILE)
	{
		fd = create_last_file(executor_state.command->out_sequence);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (executor_state.command->next)
		dup_and_close(executor_state.new_fd, STDOUT_FILENO);
	exec_command(executor_state.command, env);
}

void handle_command(t_executor *executor_state, char **env)
{
	if (executor_state->command->next)
		pipe(executor_state->new_fd);
	executor_state->pids[executor_state->command_position] = fork();
	if (executor_state->pids[executor_state->command_position] == 0)
		exec_child_command(*executor_state, env);
	if (executor_state->command_position > 0)
		close_fd(executor_state->old_fd);
	if (executor_state->command->next)
	{
		executor_state->old_fd[0] = executor_state->new_fd[0];
		executor_state->old_fd[1] = executor_state->new_fd[1];
	}
}

int main(int ac, char **av, char **env)
{
	int           i = 0;
	const t_lexer lexer = new_lexer("cat << EOF > fofa < srcs/executor.c << EOF > llllll | wc -l > x > y > z");
	t_parser     *parser = parser_new(lexer);
	t_executor    executor_state;
	executor_state.command = start_parser(parser);

	executor_state.command_position = 0;
	while (executor_state.command)
	{
		handle_command(&executor_state, env);
		executor_state.command_position += 1;
		executor_state.command = executor_state.command->next;
	}
	waitpids(executor_state.pids, executor_state.command_position);
	return 0;
}