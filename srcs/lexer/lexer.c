/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:52:36 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/23 13:40:28 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	new_lexer(const char *input)
{
	t_lexer	l;

	l.input = ft_strdup(input);
	l.read_position = 0;
	l.position = 0;
	read_char(&l);
	return (l);
}

t_token	new_token(const char *type, const char *literal)
{
	t_token	tok;

	tok.literal = ft_strdup(literal);
	tok.type = type;
	return (tok);
}

t_token	next_token(t_lexer *lexer)
{
	t_token	tok;

	skip_whitespace(lexer);
	if (lexer->ch == '$')
	{
		read_char(lexer);
		if (is_separator(lexer->ch))
		{
			return (new_token(ARG, "$"));
		}
		else if (lexer->ch == '?')
		{
			read_char(lexer);
			return (new_token(ARG, "?"));
		}
		else
		{
			tok = read_arg_no_quotes(lexer);
			if (ft_strcmp(tok.type, INVALID) != 0)
				expand(lexer, tok.literal);
			free(tok.literal);
		}
	}
	return (lex_token(lexer));
}
