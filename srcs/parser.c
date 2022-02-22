#include "parser.h"
#include "lexer/lexer.h"
#include "strtools/strtools.h"
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
	{
		free(p->curr_tok.literal);
		p->curr_tok.literal = NULL;
	}
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
	*command = (t_command){
	    .arg = NULL,
	    .in_sequence = NULL,
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

void raise_syntax_error(const char *expected, t_parser *parser, t_command *command)
{
	put_error("\tSyntax Error 🙀 ✋ ⛔️ \n");
	put_error("expected\t✅ : ");
	put_error(expected);
	put_error("\n");
	put_error("found\t\t❌ : ");
	put_error(parser->peek_tok.literal);
	put_error("\n");
	delete_parser(parser);
	delete_command(command);
	exit(EXIT_FAILURE);
}

void add_io(t_io **io_head, t_io value)
{
	t_io *new_io = malloc(sizeof(*new_io));
	t_io *tail = *io_head;

	*new_io = value;
	if (*io_head == NULL)
	{
		*io_head = new_io;
		return;
	}
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new_io;
}

void set_parsing_state(t_parser *parser)
{
	if (curr_tok_is(parser, ARG))
		parser->parsing_state = parse_arg;
	else if (curr_tok_is(parser, PIPE))
		parser->parsing_state = parse_pipe;
	else if (curr_tok_is(parser, R_REDIRECTION))
		parser->parsing_state = parse_out_redirect;
	else if (curr_tok_is(parser, APPEND))
		parser->parsing_state = parse_append;
	else if (curr_tok_is(parser, L_REDIRECTION))
		parser->parsing_state = parse_in_redirect;
	else if (curr_tok_is(parser, HEREDOC))
		parser->parsing_state = parse_heredoc;
	else
		parser->parsing_state = NULL;
}

void parse_arg(t_parser *parser, t_command *cmd)
{
	append_arg(&cmd->arg, parser->curr_tok.literal);
}

void parse_pipe(t_parser *parser, t_command *cmd)
{
	if (cmd->out_sequence == NULL)
		add_io(&cmd->out_sequence, (t_io){IO_PIPE, NULL, NULL});
	parser->parsing_state = NULL;
}

void parse_out_redirect(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
		raise_syntax_error(ARG, parser, cmd);
	next_tok(parser);
	add_io(&cmd->out_sequence,
	               (t_io){IO_FILE, ft_strdup(parser->curr_tok.literal), NULL});
}

void parse_append(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
		raise_syntax_error(ARG, parser, cmd);
	next_tok(parser);
	add_io(&cmd->out_sequence,
	               (t_io){IO_FILE_APPEND, ft_strdup(parser->curr_tok.literal), NULL});
}

void parse_in_redirect(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
		raise_syntax_error(ARG, parser, cmd);
	next_tok(parser);
	add_io(&cmd->in_sequence,
		   (t_io){IO_FILE, ft_strdup(parser->curr_tok.literal), NULL});
}

void parse_heredoc(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
		raise_syntax_error(ARG, parser, cmd);
	next_tok(parser);
	add_io(&cmd->in_sequence,
		   (t_io){IO_HEREDOC, ft_strdup(parser->curr_tok.literal), NULL});
}

t_command *parse_command(t_parser *parser)
{
	t_command *command;

	set_parsing_state(parser);
	if (parser->parsing_state == NULL)
		return (NULL);
	command = create_command();
	while (parser->parsing_state)
	{
		parser->parsing_state(parser, command);
		if (peek_tok_is(parser, INVALID))
			raise_syntax_error("VALID TOKEN", parser, command);
		next_tok(parser);
		if (parser->parsing_state != NULL)
			set_parsing_state(parser);
	}
	return (command);
}

t_command *start_parser(t_parser *parser)
{
	t_command *command;
	t_command       *current;

	command = parse_command(parser);
	if (command == NULL)
		return (command);
	current = (t_command *) command;
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

void delete_parser(t_parser *p)
{
	if (p->curr_tok.literal)
		free(p->curr_tok.literal);
	if (p->peek_tok.literal)
		free(p->peek_tok.literal);
	free(p);
}

void delete_args(t_arg *head)
{
	t_arg *current;
	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}
}

void delete_io(t_io *head)
{
	t_io *current;
	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}
}

void delete_command(t_command *head)
{
	t_command *current;

	while (head)
	{
		current = head;
		head = head->next;
		delete_args(current->arg);
		delete_io(current->out_sequence);
		delete_io(current->in_sequence);
		free(current);
	}
}
