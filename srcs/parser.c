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
	*p = (t_parser){l, {NULL, NULL}, {NULL, NULL}};
	next_tok(p);
	next_tok(p);
	return (p);
}

void next_tok(t_parser *p)
{
	free(p->curr_tok.literal);
	p->curr_tok = p->peek_tok;
	p->peek_tok = next_token(&p->lexer);
}

void append_arg(t_arg *current_arg, t_parser *p)
{
	current_arg = current_arg->next;
	while (current_arg)
		current_arg = current_arg->next;
	current_arg = malloc(sizeof(*current_arg));
	current_arg->val = ft_strdup(p->curr_tok.literal);
	current_arg->next = NULL;
}

t_command *create_command()
{
	t_command *command;

	command = malloc(sizeof(*command));
	*command = (t_command){
	    .arg = {NULL, NULL},
	    .in = {IO_STDIN, NULL},
	    .out = {IO_STDOUT, NULL},
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

void raise_syntax_error(const char *expected, const char *found)
{
	panic("expected: %s\n"
	      "found: %s\n",
	      expected, found);
}

t_command *parse_command(t_parser *parser)
{
	t_command *command;

	command = create_command();
	if (curr_tok_is(parser, ARG))
	{
		command->arg.val = ft_strdup(parser->curr_tok.literal);
		next_tok(parser);
		while (curr_tok_is(parser, ARG))
		{
			append_arg(&command->arg, parser);
			next_tok(parser);
		}
		if (curr_tok_is(parser, PIPE))
		{
			command->out.type = IO_PIPE;
			return command;
		}
		else if (curr_tok_is(parser, R_REDIRECTION))
		{
			command->out.type = IO_FILE;
			next_tok(parser);
			if (curr_tok_is(parser, ARG))
				command->out.value = ft_strdup(parser->curr_tok.literal);
			else
				raise_syntax_error(ARG, parser->curr_tok.type);
		}
		else if (curr_tok_is(parser, L_REDIRECTION))
		{
			command->in.type = IO_FILE;
			next_tok(parser);
			if (curr_tok_is(parser, ARG))
				command->in.value = ft_strdup(parser->curr_tok.literal);
			else
				raise_syntax_error(ARG, parser->curr_tok.type);
		}
		else if (curr_tok_is(parser, APPEND))
		{
			command->out.type = IO_FILE_APPEND;
			next_tok(parser);
			if (curr_tok_is(parser, ARG))
				command->out.value = ft_strdup(parser->curr_tok.literal);
			else
				raise_syntax_error(ARG, parser->curr_tok.type);
		}
		else if (curr_tok_is(parser, HEREDOC))
		{
			command->out.type = IO_FILE_APPEND;
			next_tok(parser);
			if (curr_tok_is(parser, ARG))
				command->out.value = ft_strdup(parser->curr_tok.literal);
			else
				raise_syntax_error(ARG, parser->curr_tok.type);
		}
		next_tok(parser);
	}
	else
		return (NULL);
	return (command);
}

t_command *start_parser(t_parser *parser)
{
	t_command *command;
	t_command *current = command;

	while ((current = parse_command(parser)))
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
