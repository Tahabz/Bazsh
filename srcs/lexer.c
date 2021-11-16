#include "lexer.h"
#include "token/token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: almost every call of str_join() causes a memory leak
// TOTHINKABOUT: consider expading variables during parsing and calling lexer for each one

t_lexer	new_lexer(const char *input)
{
	t_lexer	l;

	l.input = ft_strdup(input);
	l.read_position = 0;
	l.position = 0;
	read_char(&l);
	return (l);
}

t_token	read_arg_squotes(t_lexer *lexer)
{
	t_token tok;
	const int position = lexer->position;

	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\'')
		{
			tok.literal = ft_substr(lexer->input, position, lexer->position - position);
			tok.type = SINGLE_Q_ARG;
			return (tok);
		}
		read_char(lexer);
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = INVALID;
	return (tok);
}

t_token	read_arg_dquotes(t_lexer *lexer)
{
	t_token tok;
	const int position = lexer->position;

	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\"')
		{
			tok.literal = ft_substr(lexer->input, position, lexer->position - position);
			tok.type = DOUBLE_Q_ARG;
			return (tok);
		}
		read_char(lexer);
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = INVALID;
	return (tok);
}

t_token	read_arg_no_quotes(t_lexer *lexer)
{
	t_token tok;
	const int position = lexer->position;

	while (is_separator(lexer->ch) == false)
	{
		read_char(lexer);
		if (lexer->ch == '$')
			break ;
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = ARG;
	return (tok);
}

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

void	expand(t_lexer *l, const char *ident) {
	char *var;
	char *new_input;
	char *temp_sub;
	char *temp_join;
	const size_t ident_l = ft_strlen(ident) + 1;

	var = getenv(ident);
	temp_sub = ft_substr(l->input, 0, l->position - ident_l);
	temp_join = ft_strjoin(temp_sub, var);
	free(temp_sub);
	temp_sub = ft_substr(l->input,l->position + ident_l - 2, ft_strlen(l->input));
	new_input = ft_strjoin(temp_join, temp_sub);
	free(temp_sub);
	free(temp_join);
	free(l->input);
	l->input = new_input;
	l->position -= ident_l;
	l->read_position = l->position + 1;
	l->ch = l->input[l->position];
}

t_token	next_token(t_lexer *lexer)
{
	t_token tok;


	if (lexer->ch == '$') {
		if (is_separator(peek_char(lexer))
		&& peek_char(lexer) != '=') // NOTE: how about a tab or any other separator?
		{
			tok = new_token(ARG, "$");
			read_char(lexer);
			return (tok);
		}
		else
		{
			read_char(lexer);
			t_token ident_tok = read_arg_no_quotes(lexer);
			if (strcmp(ident_tok.type, INVALID) != 0)
				expand(lexer, ident_tok.literal);
			free(ident_tok.literal);
		}
	}

	if (lexer->ch == '"') {
		read_char(lexer);
		tok = read_arg_dquotes(lexer);
	}
	else if (lexer->ch == '=')
	{
		tok = new_token(EQUAL, "=");
	}
	else if (lexer->ch == ' ')
	{
		tok = new_token(SPACE, " ");
	}
	else if (lexer->ch == '\t')
	{
		tok = new_token(TAB, "\t");
	}
	else if (lexer->ch == '\'') {
		read_char(lexer);
		tok = read_arg_squotes(lexer);
	}
	else if (lexer->ch == '|') {
		if (peek_char(lexer) == '|')
		{
			read_char(lexer);
			tok = new_token(INVALID, "||");
		}
		else
			tok = new_token(PIPE, "|");
	}
	else if (lexer->ch == '>' && peek_char(lexer) == '>')
	{
		read_char(lexer);
		tok = new_token(APPEND, ">>");
	}
	else if (lexer->ch == '>') {
		tok = new_token(R_REDIRECTION, ">");
	}
	else if (lexer->ch == '<' && peek_char(lexer) == '<')
	{
		read_char(lexer);
		tok = new_token(HEREDOC, "<<");
	}
	else if (lexer->ch == '<') {
		tok = new_token(L_REDIRECTION, "<");
	}
	else if (lexer->ch == '\0')
		tok = new_token(EOF_, "\0");
	else {
		tok = read_arg_no_quotes(lexer);
		return (tok);
	}
	read_char(lexer);
	return (tok);
}
