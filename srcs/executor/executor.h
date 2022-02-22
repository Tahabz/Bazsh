/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:49:19 by mobaz             #+#    #+#             */
/*   Updated: 2022/02/22 21:02:25 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../srcs/parser.h"
# include "../arr_tools/arr_tools.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

typedef struct s_signal
{
	int		status;
	bool	forked;
	char	*code;
}				t_signal;
typedef struct s_executor
{
	int			new_fd[2];
	int			old_fd[2];
	int			command_position;
	int			pids[1000];
	char		*commands_paths[1000];
	char		**commands_args[1000];
	t_command	*command;
	char		***env;
}				t_executor;
typedef struct s_parent_command
{
	bool	is_parent_command;
	int		(*handler)(t_arg *, char ***);
}				t_parent_command;

typedef struct t_child_command
{
	bool	is_child_command;
	int		(*handler)(t_arg *, char **);
}				t_child_command;
typedef struct s_file
{
	int		fd;
	char	*error;
}				t_file;

t_signal			g_signal;
void				ft_exit(t_arg *arg, char **env);
int					cd(t_arg *args, char ***env);
int					export(t_arg *arg, char ***env);
bool				is_not_empty_ident(char *str);
bool				is_empty_ident(char *str);
bool				is_ident(char *ident);
int					unset(t_arg *arg, char ***env);
bool				keys_cmp(char *str, char *key);
void				free_double_pointer(char **arr);
void				delete_executor(t_executor executor);
int					list_count(t_arg *arg);
int					pwd(t_arg *arg, char **env);
int					echo(t_arg *arg, char **env);
int					get_var_index(const char *var_name, char **env);
char				*make_env_name(char *var_name, char *var_value);
void				set_env(char *var_name, char *var_value, char ***env);
char				*ft_getenv(const char *var_name, char **env);
int					env(t_arg *arg, char **env);
int					get_last_fd(t_io *sequence, int callback(t_io *));
int					create_file(t_io *sequence);
int					open_file(t_io *sequence);
void				write_line(const char *line, int fd);
void				replace_sequence(t_io *sequence,
						const char *value, enum io_type newtype);
char				**copy_env(char **env);
void				exec_child_command(t_executor executor_state, char **env);
void				handle_command(t_executor *executor_state, char ***env);
void				exec_command(t_executor executor_state, char **env);
t_child_command		is_child_command(char *command_name);
t_parent_command	is_parent_command(char *command_name);
char				*join_path(char *str1, char *str2);
char				*get_command_path(char *command_name, char **env);
void				close_fd(int fd[]);
void				dup_and_close(int fd[], int file_no);
void				write_to_file(char *delim, int file_num, int fd);
int					handle_heredoc(t_executor *executor);
bool				keys_cmp(char *str, char *key);
void				waitpids(int pids[], size_t i);
void				close_fd(int fd[]);
void				dup_and_close(int fd[], int file_no);
void				free_all_memory(t_executor executor, t_parser *parser);
void				set_status_code(int code);
void				signal_handler(int signal);
void				ignctl(void);
void				set_status_code(int code);
void				init_signals(void);
int					p_error(const char *arg, const char *arg2,
						const char *message, int code);
void				handle_errors(char *cmd, char **env);
t_child_command		is_child_command(char *command_name);
t_parent_command	is_parent_command(char *command_name);
void				handle_in_sequence(t_executor executor, int *fd);
void				handle_out_sequence(t_executor executor, int *fd);
#endif
