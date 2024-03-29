/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:52:58 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/22 21:53:00 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	read_char(t_lexer *lexer)
{
	if (lexer->read_position >= ft_strlen(lexer->input))
		lexer->ch = '\0';
	else
		lexer->ch = lexer->input[lexer->read_position];
	lexer->position = lexer->read_position;
	lexer->read_position += 1;
}

char	peek_char(t_lexer *lexer)
{
	if (lexer->read_position < ft_strlen(lexer->input))
		return (lexer->input[lexer->read_position]);
	return ('\0');
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->ch == ' ' || lexer->ch == '\t')
	{
		read_char(lexer);
	}
}

int	is_separator(const char ch)
{
	return (ch == '|'
		|| ch == '\t'
		|| ch == '>'
		|| ch == '<'
		|| ch == ' '
		|| ch == '\"'
		|| ch == '\''
		|| ch == '\0');
}
