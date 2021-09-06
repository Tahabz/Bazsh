#include "lexer.h"
#include "libft/libft.h"
#include "token/token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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
	int position;
	char *word;

	position = lexer->position;
	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\'')
		{
			word = ft_substr(lexer->input, position, lexer->position - position);
			return ((t_token) {lookup_ident(word), word});
		}
		read_char(lexer);
	}
	word = ft_substr(lexer->input, position, lexer->position - position);
	return ((t_token) {g_invalid, word});
}

bool						is_escapable(char c)
{
	const char escapables[] = {'$', '\\', '"', '*', '@'};
	const size_t n_escapables = sizeof(escapables)/sizeof(escapables[0]);
	size_t i;

	i = 0;
	while (i < n_escapables)
	{
		if (escapables[i] == c)
			return (true);
		i++;
	}
	return (false);
}

t_token						read_arg_dquotes(t_lexer *lexer)
{
	char *ident;
	t_token tok;

	ident = NULL;
	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\\' && is_escapable(peek_char(lexer))) {
			read_char(lexer);
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		}
		else if (lexer->ch == '\"')
		{
			tok.type = lookup_ident(ident);
			tok.literal = ident;
			return (tok);
		}
		else
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		read_char(lexer);
	}
	tok.type = g_invalid;
	tok.literal = ident;
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
			|| ch == ' ');
}

char						*read_arg_no_quotes(t_lexer *lexer)
{
	char *ident;

	ident = NULL;
	while (lexer->ch != '\0' && !is_separator(lexer->ch) && lexer->ch != '$')
	{
		if (lexer->ch == '"')
		{
			read_char(lexer); // To advance beyond the opening "
			const char *temp = read_arg_dquotes(lexer).literal;
			read_char(lexer); // To advance beyond the closing "
			ident = ft_strjoin(ident, (char *)temp);
		}
		if (lexer->ch == '\'')
		{
			read_char(lexer); // To advance beyond the opening '
			const char *temp = read_arg_squotes(lexer).literal;
			read_char(lexer); // To advance beyond the closing '
			ident = ft_strjoin(ident, (char *)temp);
		}
		if (lexer->ch == '\\')
		{
			read_char(lexer);
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		}
		else
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		read_char(lexer);
	}
	return (ident);
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

void expand(t_lexer *l, char *ident) {
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
		if (peek_char(lexer) == ' ') // NOTE: how about a tab or any other separator?
			tok = new_token(g_arg, "$");
		else
		{
			read_char(lexer);
			expand(lexer, read_arg_no_quotes(lexer));
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
		tok.literal = read_arg_no_quotes(lexer);
		tok.type = lookup_ident(tok.literal);
		return (tok);
	}
	read_char(lexer);
	return (tok);
}

t_token		new_token(const char *type, const char *literal)
{
	t_token tok;
	tok.literal = literal;
	tok.type = type;
	return (tok);
}
