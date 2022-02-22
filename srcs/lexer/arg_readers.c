/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_readers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:51:59 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/22 21:52:01 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	get_next_arg(t_lexer *lexer)
{
	t_token	next_tok;

	next_tok = (t_token){};
	if (lexer->ch == '"')
	{
		read_char(lexer);
		next_tok = read_arg_dquotes(lexer);
	}
	else if (lexer->ch == '\'')
	{
		read_char(lexer);
		next_tok = read_arg_squotes(lexer);
	}
	else if (!is_separator(lexer->ch))
	{
		next_tok = read_arg_no_quotes(lexer);
	}
	return (next_tok);
}

static t_token	join_next_arg(t_lexer *lexer, t_token current_tok)
{
	t_token		next_tok;
	const char	*temp = current_tok.literal;

	next_tok = get_next_arg(lexer);
	current_tok.literal = ft_strjoin(current_tok.literal, next_tok.literal);
	free(next_tok.literal);
	free((void *) temp);
	current_tok.type = next_tok.type;
	return (current_tok);
}

t_token	read_arg_squotes(t_lexer *lexer)
{
	t_token				tok;
	const unsigned int	position = lexer->position;

	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\'')
		{
			tok.literal = ft_substr(lexer->input, position,
					lexer->position - position);
			tok.type = ARG;
			if (peek_char(lexer) == '\"' || peek_char(lexer) == '\''
				|| !is_separator(peek_char(lexer)))
			{
				read_char(lexer);
				tok = join_next_arg(lexer, tok);
			}
			return (tok);
		}
		read_char(lexer);
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = INVALID;
	return (tok);
}

t_token	read_arg_dquotes(t_lexer *l)
{
	t_token				tok;
	const unsigned int	pos = l->position;

	while (l->ch != '\0')
	{
		if (l->ch == '$' && !is_separator(peek_char(l)))
			expand_quoted(l);
		if (l->ch == '\"')
		{
			tok.literal = ft_substr(l->input, pos, l->position - pos);
			tok.type = ARG;
			if (peek_char(l) == '\"' || peek_char(l) == '\''
				|| !is_separator(peek_char(l)))
			{
				read_char(l);
				tok = join_next_arg(l, tok);
			}
			return (tok);
		}
		read_char(l);
	}
	return ((t_token){.type = INVALID,
		.literal = ft_substr(l->input, pos, l->position - pos)});
}

t_token	read_arg_no_quotes(t_lexer *lexer)
{
	t_token				tok;
	const unsigned int	position = lexer->position;

	while (is_separator(lexer->ch) == false)
	{
		read_char(lexer);
		if (lexer->ch == '$')
			break ;
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = ARG;
	if (lexer->ch == '\"' || lexer->ch == '\'')
	{
		tok = join_next_arg(lexer, tok);
	}
	return (tok);
}
