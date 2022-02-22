/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   parser.c                                      000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 22:32:48 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 22:32:48 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../lexer/lexer.h"
#include "../strtools/strtools.h"
#include <stdio.h>
#include <stdlib.h>

t_parser	*parser_new(t_lexer l)
{
	t_parser	*p;

	p = malloc(sizeof(*p));
	*p = (t_parser){l, {NULL, NULL}, {NULL, NULL}, NULL};
	next_tok(p);
	next_tok(p);
	return (p);
}

t_command	*start_parser(t_parser *parser)
{
	t_command	*command;
	t_command	*current;

	if (curr_tok_is(parser, PIPE))
		raise_syntax_error("other than PIPE", parser, NULL);
	command = parse_command(parser);
	if (command == NULL)
		return (command);
	current = (t_command *) command;
	current->next = parse_command(parser);
	while (current->next)
	{
		current = current->next;
	}
	return (command);
}
