#include "lexer.h"
#include "token/token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: almost every call of str_join() causes a memory leak
// TOTHINKABOUT: consider expading variables during parsing and calling lexer for each one

t_lexer		new_lexer(char *input)
{
	t_lexer l;
	l.input = input;
	l.read_position = 0;
	l.position = 0;
	read_char(&l);
	return (l);
}

t_token						read_arg_squotes(t_lexer *lexer)
{
	t_token tok;
	const int position = lexer->position;

	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\'')
		{
			tok.literal = ft_substr(lexer->input, position, lexer->position - position);
			tok.type = lookup_ident(tok.literal);
			if (tok.type != NULL)
				return (tok);
			tok.type = g_sqarg;
			return (tok);
		}
		read_char(lexer);
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = g_invalid;
	return (tok);
}

t_token						read_arg_dquotes(t_lexer *lexer)
{
	t_token tok;
	const int position = lexer->position;

	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\"')
		{
			tok.literal = ft_substr(lexer->input, position, lexer->position - position);
			tok.type = lookup_ident(tok.literal);
			if (tok.type != NULL)
				return (tok);
			tok.type = g_dqarg;
			return (tok);
		}
		read_char(lexer);
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = g_invalid;
	return (tok);
}

int		is_separator(const char ch)
{
	return (ch == '|'
			|| ch == '&'
			|| ch == ';'
			|| ch == '\t'
			|| ch == '>'
			|| ch == '<'
			|| ch == '='
			|| ch == ' '
			|| ch == '\"'
			|| ch == '\'');
}

t_token						read_arg_no_quotes(t_lexer *lexer)
{
	t_token tok;
	const int position = lexer->position;

	while (lexer->ch != '\0' && is_separator(lexer->ch) == false)
	{
		read_char(lexer);
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = lookup_ident(tok.literal);
	if (tok.type != NULL)
		return (tok);
	tok.type = g_arg;
	return (tok);
}

void			read_char(t_lexer *lexer)
{
	if (lexer->read_position >= strlen(lexer->input))
		lexer->ch = '\0';
	else
		lexer->ch = lexer->input[lexer->read_position];
	lexer->position = lexer->read_position;
	lexer->read_position += 1;
}

char			peek_char(t_lexer *lexer)
{
	if (lexer->read_position < strlen(lexer->input))
		return (lexer->input[lexer->read_position]);
	return ('\0');
}

void expand(t_lexer *l, const char *ident) {
	char *var;
	char *new_input;
	char *temp_sub;
	char *temp_join;
	const size_t ident_l = ft_strlen(ident) + 1;

	// TODO: to free or not to free
	// TODO: to protect or not to protect
	var = getenv(ident);
	// TODO: to free or not to free
	temp_sub = ft_substr(l->input, 0, l->position - ident_l);
	temp_join = ft_strjoin(temp_sub, var);
	free(temp_sub);
	// TODO: to free or not to free
	temp_sub = ft_substr(l->input,l->position + ident_l - 2, ft_strlen(l->input));
	new_input = ft_strjoin(temp_join, temp_sub);
	free(temp_sub);
	free(temp_join);
	/* free(l->input); */
	/*
	* NOTE: It's actually a bad idea to free l->input here
	*		because it will be freed later as line in main.c
	*/
	l->input = new_input;
	l->position -= ident_l;
	l->read_position = l->position + 1;
	l->ch = l->input[l->position];
}

t_token		next_token(t_lexer *lexer)
{
	t_token tok;


	if (lexer->ch == '$') {
		if (peek_char(lexer) == ' ' || peek_char(lexer) == '\0') // NOTE: how about a tab or any other separator?
		{
			tok = new_token(g_invalid, "$");
			read_char(lexer);
			return (tok);
		}
		else
		{
			read_char(lexer);
			t_token ident_tok = read_arg_no_quotes(lexer);
			if (strcmp(ident_tok.type, g_invalid) != 0)
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
		tok.literal = "=";
		tok.type = g_equal;
	}
	else if (lexer->ch == ' ')
	{
		tok.literal = " ";
		tok.type = 	g_space;
	}
	else if (lexer->ch == '\t')
	{
		tok.literal = "\t";
		tok.type = g_tab;
	}
	else if (lexer->ch == '\'') {
		read_char(lexer);
		tok = read_arg_squotes(lexer);
	}
	else if (lexer->ch == '|') {
		if (peek_char(lexer) == '|')
		{
			read_char(lexer);
			tok = new_token(g_or, "||");
		}
		else
			tok = new_token(g_pipe, "|");
	}
	else if (lexer->ch == '&') {
		if (peek_char(lexer) == '&')
		{
			tok = new_token(g_and, "&&");
			read_char(lexer);
		}
		else
			tok = new_token(g_ampersand, "&");
	}
	else if (lexer->ch == '>' && peek_char(lexer) == '>')
	{
		read_char(lexer);
		tok.literal = ">>";
		tok.type = g_a_redirection;
	}
	else if (lexer->ch == '>') {
		tok.literal = ">";
		tok.type = g_r_redirection;
	}
	else if (lexer->ch == '<' && peek_char(lexer) == '<')
	{
		read_char(lexer);
		tok.literal = "<<";
		tok.type = g_heredoc;
	}
	else if (lexer->ch == '<') {
		tok.literal = "<";
		tok.type = g_l_redirection;
	}
	else if (lexer->ch == '\0')
		tok = new_token(g_eof, "\0");
	else if (lexer->ch == ';')
		tok = new_token(g_seperator, ";");
	else {
		tok = read_arg_no_quotes(lexer);
		return (tok);
	}
	read_char(lexer);
	return (tok);
}

t_token		new_token(const char *type, const char *literal)
{
	t_token tok;
	tok.literal = ft_strdup(literal);
	tok.type = type;
	return (tok);
}
