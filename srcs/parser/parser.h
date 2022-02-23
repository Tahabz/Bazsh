/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:17:02 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/23 14:38:33 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../lexer/lexer.h"
# include <stdarg.h>

typedef struct s_parser		t_parser;
typedef struct s_command	t_command;
typedef void				t_parsing_state(t_parser *parser, t_command *cmd);

typedef struct s_parser
{
	t_lexer			lexer;
	t_token			curr_tok;
	t_token			peek_tok;
	t_parsing_state	*parsing_state;
}	t_parser;

enum e_io_type
{
	IO_STDIN,
	IO_STDOUT,
	IO_STDERR,
	IO_FILE,
	IO_FILE_APPEND,
	IO_HEREDOC,
	IO_PIPE
};

typedef struct s_io
{
	enum e_io_type	type;
	char			*value;
	struct s_io		*next;
}	t_io;

typedef struct s_arg
{
	char			*val;
	struct s_arg	*next;
}	t_arg;

typedef struct s_command
{
	t_arg				*arg;
	t_io				*in_sequence;
	t_io				*out_sequence;
	struct s_command	*next;
}	t_command;

t_command	*parse_command(t_parser *parser);
t_command	*start_parser(t_parser *parser);
bool		curr_tok_is(const t_parser *parser, const char *tok);
bool		peek_tok_is(const t_parser *parser, const char *tok);
bool		expect_peek(t_parser *parser, const char *tok);
void		parse_arg(t_parser *parser, t_command *cmd);
void		parse_pipe(t_parser *parser, t_command *cmd);
void		parse_out_redirect(t_parser *parser, t_command *cmd);
void		parse_append(t_parser *parser, t_command *cmd);
void		parse_in_redirect(t_parser *parser, t_command *cmd);
void		parse_heredoc(t_parser *parser, t_command *cmd);
void		set_parsing_state(t_parser *parser);
void		raise_syntax_error(const char *expected, t_parser *parser);
void		next_tok(t_parser *p);
t_parser	*parser_new(t_lexer l);
void		delete_parser(t_parser *p);
void		delete_command(t_command *head);
void		delete_io(t_io *head);
void		delete_args(t_arg *head);
t_arg		*new_arg(const char *value);
void		append_arg(t_arg **head_arg, const char *value);
t_command	*create_command(void);
void		add_io(t_io **io_head, t_io value);

#endif
