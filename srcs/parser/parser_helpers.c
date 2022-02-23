/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:17:02 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/23 14:39:04 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_arg(t_parser *parser, t_command *cmd)
{
	append_arg(&cmd->arg, parser->curr_tok.literal);
}

void	parse_pipe(t_parser *parser, t_command *cmd)
{
	if (cmd->out_sequence == NULL)
		add_io(&cmd->out_sequence, (t_io){IO_PIPE, NULL, NULL});
	parser->parsing_state = NULL;
}

void	parse_out_redirect(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
		raise_syntax_error(ARG, parser);
	next_tok(parser);
	add_io(&cmd->out_sequence,
		(t_io){IO_FILE, ft_strdup(parser->curr_tok.literal), NULL});
}

void	parse_append(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
		raise_syntax_error(ARG, parser);
	next_tok(parser);
	add_io(&cmd->out_sequence,
		(t_io){IO_FILE_APPEND, ft_strdup(parser->curr_tok.literal), NULL});
}

void	parse_in_redirect(t_parser *parser, t_command *cmd)
{
	if (peek_tok_is(parser, ARG) == false)
		raise_syntax_error(ARG, parser);
	next_tok(parser);
	add_io(&cmd->in_sequence,
		(t_io){IO_FILE, ft_strdup(parser->curr_tok.literal), NULL});
}
