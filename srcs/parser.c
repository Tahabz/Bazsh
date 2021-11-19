#include "parser.h"
#include "lexer.h"
#include "strtools/strtools.h"
#include "token/token.h"
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
	p->curr_tok = p->peek_tok;
	p->peek_tok = next_token(&p->lexer);
}

t_command *parse_command(t_parser *parser)
{
	t_command *command;

	command = malloc(sizeof(*command));
	if (curr_tok_is(parser, ARG))
		command->name = strdup(parser->curr_tok.literal);
	else
		return (NULL);
	return (command);
}

t_command *start_parser(t_parser *parser)
{
	t_command *command = malloc(sizeof(*command));
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
