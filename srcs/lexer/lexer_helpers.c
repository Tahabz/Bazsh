/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:52:45 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/22 21:52:46 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	lex_out_redirect_or_append(t_lexer *lexer)
{
	t_token	tok;

	if (peek_char(lexer) == '>')
	{
		read_char(lexer);
		tok = new_token(APPEND, ">>");
	}
	else
		tok = new_token(R_REDIRECTION, ">");
	return (tok);
}

static t_token	lex_in_redirect_or_heredoc(t_lexer *lexer)
{
	t_token	tok;

	if (peek_char(lexer) == '<')
	{
		read_char(lexer);
		tok = new_token(HEREDOC, "<<");
	}
	else
		tok = new_token(L_REDIRECTION, "<");
	return (tok);
}

static t_token	lex_double_quotes(t_lexer *lexer)
{
	read_char(lexer);
	return (read_arg_dquotes(lexer));
}

static t_token	lex_single_quotes(t_lexer *lexer)
{
	read_char(lexer);
	return (read_arg_squotes(lexer));
}

t_token	lex_token(t_lexer *lexer)
{
	t_token	tok;

	if (lexer->ch == '"')
		tok = lex_double_quotes(lexer);
	else if (lexer->ch == '\'')
		tok = lex_single_quotes(lexer);
	else if (lexer->ch == '|')
		tok = new_token(PIPE, "|");
	else if (lexer->ch == '>')
		tok = lex_out_redirect_or_append(lexer);
	else if (lexer->ch == '<')
		tok = lex_in_redirect_or_heredoc(lexer);
	else if (lexer->ch == '\0')
		tok = new_token(EOF_, "\0");
	else
	{
		tok = read_arg_no_quotes(lexer);
		return (tok);
	}
	read_char(lexer);
	return (tok);
}
