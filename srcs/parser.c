#include "parser.h"
#include "lexer.h"
#include "strtools/strtools.h"
#include "token/token.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

t_parser *parser_new(t_lexer l)
{
	t_parser *p = malloc(sizeof(*p));
	*p = (t_parser){l, {NULL, NULL}, {NULL, NULL}, NULL};
	next_tok(p);
	next_tok(p);
	return (p);
}

void next_tok(t_parser *p)
{
	if (p->curr_tok.literal != NULL)
		free(p->curr_tok.literal);
	p->curr_tok = p->peek_tok;
	p->peek_tok = next_token(&p->lexer);
}

t_arg *new_arg(const char *value)
{
	t_arg *arg = malloc(sizeof(*arg));
	arg->val = ft_strdup(value);
	arg->next = NULL;
	return arg;
}

void append_arg(t_arg **head_arg, const char *value)
{
	t_arg *tail;

	tail = *head_arg;
	if (*head_arg == NULL)
	{
		*head_arg = new_arg(value);
		return;
	}
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new_arg(value);
}

t_command *create_command()
{
	t_command *command;

	command = malloc(sizeof(*command));
	// NOTE: should the out take a default value
	*command = (t_command){
	    .arg = NULL,
	    .in = {IO_STDIN, NULL},
	    .out_sequence = NULL,
	    .next = NULL,
	};
	return (command);
}

void panic(const char *str_format, ...)
{
	va_list args;
	va_start(args, str_format);
	printf(str_format, args);
	va_end(args);
	exit(1);
}

void put_error(const char *str)
{
	write(2, str, ft_strlen(str));
}

void raise_syntax_error(const char *expected, const char *found)
{
	put_error("\tSyntax Error 🙀 ✋ ⛔️ \n");
	put_error("expected\t✅ : ");
	put_error(expected);
	put_error("\n");
	put_error("found\t\t❌ : ");
	put_error(found);
	put_error("\n");
}

void add_output_dst(t_io **io_head, t_io value)
{
	t_io *new_output_dst = malloc(sizeof(*new_output_dst));
	t_io *tail = *io_head;

	*new_output_dst = value;
	if (*io_head == NULL)
	{
		*io_head = new_output_dst;
		return;
	}
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new_output_dst;
}

void parse_arg(t_parser *parser, t_command *cmd)
{
	append_arg(&cmd->arg, parser->curr_tok.literal);
	if (peek_tok_is(parser, ARG))
		parser->parsing_state = parse_arg;
	else if (peek_tok_is(parser, PIPE))
		parser->parsing_state = parse_pipe;
	else if (peek_tok_is(parser, R_REDIRECTION))
		parser->parsing_state = parse_out_redirect;
	else if (peek_tok_is(parser, APPEND))
		parser->parsing_state = parse_append;
	else if (peek_tok_is(parser, L_REDIRECTION))
		parser->parsing_state = parse_in_redirect;
	else
		parser->parsing_state = NULL;
}

void parse_pipe(t_parser *parser, t_command *cmd)
{
	if (cmd->out_sequence == NULL)
		add_output_dst(&cmd->out_sequence, (t_io){IO_PIPE, NULL, NULL});
	parser->parsing_state = NULL;
}

void parse_out_redirect(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
	{
		raise_syntax_error(ARG, parser->peek_tok.literal);
		exit(EXIT_FAILURE);
	}
	next_tok(parser);
	add_output_dst(&cmd->out_sequence,
	               (t_io){IO_FILE, ft_strdup(parser->curr_tok.literal), NULL});
	if (peek_tok_is(parser, PIPE))
		parser->parsing_state = parse_pipe;
	else if (peek_tok_is(parser, R_REDIRECTION))
		parser->parsing_state = parse_out_redirect;
	else if (peek_tok_is(parser, APPEND))
		parser->parsing_state = parse_append;
	else if (peek_tok_is(parser, L_REDIRECTION))
		parser->parsing_state = parse_in_redirect;
}

void parse_append(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
	{
		raise_syntax_error(ARG, parser->peek_tok.literal);
		exit(EXIT_FAILURE);
	}
	next_tok(parser);
	add_output_dst(&cmd->out_sequence,
	               (t_io){IO_FILE_APPEND, ft_strdup(parser->curr_tok.literal), NULL});
	if (peek_tok_is(parser, PIPE))
		parser->parsing_state = parse_pipe;
	else if (peek_tok_is(parser, R_REDIRECTION))
		parser->parsing_state = parse_out_redirect;
	else if (peek_tok_is(parser, APPEND))
		parser->parsing_state = parse_append;
	else if (peek_tok_is(parser, L_REDIRECTION))
		parser->parsing_state = parse_in_redirect;
}

void parse_in_redirect(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
	{
		raise_syntax_error(ARG, parser->peek_tok.literal);
		exit(EXIT_FAILURE);
	}
	while (peek_tok_is(parser, ARG))
		next_tok(parser);
	cmd->in = (t_io){IO_FILE, ft_strdup(parser->curr_tok.literal), NULL};
	if (peek_tok_is(parser, PIPE))
		parser->parsing_state = parse_pipe;
	else if (peek_tok_is(parser, R_REDIRECTION))
		parser->parsing_state = parse_out_redirect;
	else if (peek_tok_is(parser, APPEND))
		parser->parsing_state = parse_append;
}

t_command *parse_command(t_parser *parser)
{
	t_command *command;

	command = create_command();
	if (curr_tok_is(parser, ARG))
		parser->parsing_state = parse_arg;
	else
		return NULL;
	while (parser->parsing_state)
	{
		parser->parsing_state(parser, command);
		next_tok(parser);
		if (curr_tok_is(parser, EOF_))
			break;
	}
	return (command);
}

t_command *start_parser(t_parser *parser)
{
	const t_command *command = parse_command(parser);
	t_command       *current = (t_command *) command;

	while ((current->next = parse_command(parser)))
	{
		current = current->next;
	}
	return (command);
}

bool curr_tok_is(const t_parser *parser, const char *tok)
{
	return (str_match(parser->curr_tok.type, tok));
}

bool peek_tok_is(const t_parser *parser, const char *tok)
{
	return (str_match(parser->peek_tok.type, tok));
}

bool expect_peek(t_parser *parser, const char *tok)
{
	if (peek_tok_is(parser, tok))
	{
		next_tok(parser);
		return (true);
	}
	else
	{
		return (false);
	}
}
