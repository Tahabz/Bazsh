#include "lexer.h"
#include "strtools/strtools.h"
#include "token/token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_lexer new_lexer(const char *input)
{
	t_lexer l;

	l.input = ft_strdup(input);
	l.read_position = 0;
	l.position = 0;
	read_char(&l);
	return (l);
}

static t_token get_next_arg(t_lexer *lexer)
{
	t_token next_tok;
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
	return next_tok;
}

static t_token join_next_arg(t_lexer *lexer, t_token current_tok)
{
	t_token     next_tok;
	const char *temp = current_tok.literal;

	next_tok = get_next_arg(lexer);
	current_tok.literal = ft_strjoin(current_tok.literal, next_tok.literal);
	free(next_tok.literal);
	free((void *) temp);
	current_tok.type = next_tok.type;
	return (current_tok);
}

t_token read_arg_squotes(t_lexer *lexer)
{
	t_token   tok;
	const unsigned int position = lexer->position;

	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\'')
		{
			tok.literal = ft_substr(lexer->input, position, lexer->position - position);
			tok.type = ARG;
			if (peek_char(lexer) == '\"' || peek_char(lexer) == '\'' || !is_separator(peek_char(lexer)))
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

t_token read_arg_dquotes(t_lexer *lexer)
{
	t_token   tok;
	const unsigned int position = lexer->position;

	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\"')
		{
			tok.literal = ft_substr(lexer->input, position, lexer->position - position);
			tok.type = ARG;
			// TODO expand tok.literal variables
			if (peek_char(lexer) == '\"' || peek_char(lexer) == '\'' || !is_separator(peek_char(lexer)))
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

t_token read_arg_no_quotes(t_lexer *lexer)
{
	t_token   tok;
	const unsigned int position = lexer->position;

	while (is_separator(lexer->ch) == false)
	{
		read_char(lexer);
		if (lexer->ch == '$')
			break;
	}
	tok.literal = ft_substr(lexer->input, position, lexer->position - position);
	tok.type = ARG;
	if (lexer->ch == '\"' || lexer->ch == '\'')
	{
		tok = join_next_arg(lexer, tok);
	}
	return (tok);
}

void read_char(t_lexer *lexer)
{
	if (lexer->read_position >= ft_strlen(lexer->input))
		lexer->ch = '\0';
	else
		lexer->ch = lexer->input[lexer->read_position];
	lexer->position = lexer->read_position;
	lexer->read_position += 1;
}

char peek_char(t_lexer *lexer)
{
	if (lexer->read_position < ft_strlen(lexer->input))
		return (lexer->input[lexer->read_position]);
	return ('\0');
}

void expand(t_lexer *l, const char *ident)
{
	char        *var;
	char        *new_input;
	char        *temp_sub;
	char        *temp_join;
	const size_t ident_l = ft_strlen(ident) + 1;

	var = getenv(ident);
	temp_sub = ft_substr(l->input, 0, l->position - ident_l);
	temp_join = ft_strjoin(temp_sub, var);
	free(temp_sub);
	temp_sub = ft_substr(l->input, l->position, ft_strlen(l->input));
	new_input = ft_strjoin(temp_join, temp_sub);
	free(temp_sub);
	free(temp_join);
	free(l->input);
	l->input = new_input;
	l->position -= ident_l;
	l->read_position = l->position + 1;
	l->ch = l->input[l->position];
}

t_token next_token(t_lexer *lexer)
{
	t_token tok;

	while (lexer->ch == ' ' || lexer->ch == '\t')
		read_char(lexer);

	if (lexer->ch == '$')
	{
		if (is_separator(peek_char(lexer))) // NOTE: how about a tab or any other separator?
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

	if (lexer->ch == '"')
	{
		read_char(lexer);
		tok = read_arg_dquotes(lexer);
	}
	else if (lexer->ch == '\'')
	{
		read_char(lexer);
		tok = read_arg_squotes(lexer);
	}
	else if (lexer->ch == '|')
	{
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
	else if (lexer->ch == '>')
	{
		tok = new_token(R_REDIRECTION, ">");
	}
	else if (lexer->ch == '<' && peek_char(lexer) == '<')
	{
		read_char(lexer);
		tok = new_token(HEREDOC, "<<");
	}
	else if (lexer->ch == '<')
	{
		tok = new_token(L_REDIRECTION, "<");
	}
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
