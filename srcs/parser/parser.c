/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 22:32:48 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/23 20:40:54 by mobaz            ###   ########.fr       */
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
		raise_syntax_error("other than PIPE", parser);
	command = parse_command(parser);
	if (command == NULL)
		return (command);
	current = (t_command *) command;
	current->next = parse_command(parser);
	while (current->next)
	{
		current = current->next;
		current->next = parse_command(parser);
	}
	return (command);
}
