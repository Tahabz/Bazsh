/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:17:02 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/23 14:39:21 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_parsing_state(t_parser *parser)
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

void	parse_heredoc(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
		raise_syntax_error(ARG, parser);
	next_tok(parser);
	add_io(&cmd->in_sequence,
		(t_io){IO_HEREDOC, ft_strdup(parser->curr_tok.literal), NULL});
}

t_command	*parse_command(t_parser *parser)
{
	t_command	*command;

	set_parsing_state(parser);
	if (parser->parsing_state == NULL)
		return (NULL);
	command = create_command();
	while (parser->parsing_state)
	{
		parser->parsing_state(parser, command);
		if (peek_tok_is(parser, INVALID))
			raise_syntax_error("VALID TOKEN", parser);
		next_tok(parser);
		if (parser->parsing_state != NULL)
			set_parsing_state(parser);
	}
	return (command);
}
