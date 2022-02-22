/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   parser_error.c                                000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 23:17:02 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 23:17:02 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	curr_tok_is(const t_parser *parser, const char *tok)
{
	return (str_match(parser->curr_tok.type, tok));
}

bool	peek_tok_is(const t_parser *parser, const char *tok)
{
	return (str_match(parser->peek_tok.type, tok));
}

bool	expect_peek(t_parser *parser, const char *tok)
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

void	next_tok(t_parser *p)
{
	if (p->curr_tok.literal != NULL)
	{
		free(p->curr_tok.literal);
		p->curr_tok.literal = NULL;
	}
	p->curr_tok = p->peek_tok;
	p->peek_tok = next_token(&p->lexer);
}
