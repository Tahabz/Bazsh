#include "lexer.h"
#include "libft/libft.h"
#include "token/token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: create a new version of str_join() that consumes its arguments
// NOTE: almost every call of str_join() causes a memory leak
// TODO: handle "$VAR" (double quoted variable)
// TODO: handle "something$VAR" (double quoted variable with a prefixed token)
// TOTHINKABOUT: consider expading variables during parsing and calling lexer for each one
// TODO: handle double quotes surrounded by tokens with spaces inside (eg: hello"hello " -> "hellohello ")

t_lexer		new_lexer(char *input)
{
	t_lexer l;
	l.input = input;
	l.read_position = 0;
	l.position = 0;
	l.skip_white_spaces = &skip_white_spaces;
	l.peek_char = &peek_char;
	l.read_arg_dquotes = &read_arg_dquotes;
	l.read_arg_squotes = &read_arg_squotes;
	l.read_arg_no_quotes = &read_arg_no_quotes;
	l.read_number = &read_number;
	l.read_char = &read_char;
	l.next_token = &next_token;
	l.trim = &trim;
	l.read_char(&l);
	return (l);
}


t_return	trim(t_lexer *lexer, const char delim) {
	int 	len;
	int		i;
	int		start;

	start = lexer->position;
	i = 0;
	len = ft_strlen(lexer->input);
	while (i < len) {
		if (lexer->peek_char(lexer) == '\\') {
			lexer->read_char(lexer);
			lexer->read_char(lexer);
		}
		if (lexer->ch == delim)
			break ;
		lexer->read_char(lexer);
		i++;
	}
	t_return ret;
	ret.data = ft_substr(lexer->input, start, i);
	if (i == len)
		ret.state = "INCOMPLETED";
	else
		ret.state = "COMPLETED";
	return ret;
}

char						*read_number(t_lexer *lexer)
{
	unsigned int position;

	position = lexer->position;
	while (ft_isdigit(lexer->ch))
		lexer->read_char(lexer);
	return (ft_substr(lexer->input, position, lexer->position - position));
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
		lexer->read_char(lexer);
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

	ident = "";
	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\\' && is_escapable(lexer->peek_char(lexer))) {
			lexer->read_char(lexer);
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		}
		else if (lexer->ch == '\"')
		{
			puts(ident);
			tok.type = lookup_ident(ident);
			tok.literal = ident;
			return (tok);
		}
		else
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		lexer->read_char(lexer);
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

	ident = 0;
	while (lexer->ch != '\0' && !is_separator(lexer->ch) && lexer->ch != '$')
	{
		if (lexer->ch == '"')
		{
			lexer->read_char(lexer); // To advance beyond the opening "
			const char *temp = read_arg_dquotes(lexer).literal;
			lexer->read_char(lexer); // To advance beyond the closing "
			ident = ft_strjoin(ident, (char *)temp);
		}
		if (lexer->ch == '\'')
		{
			lexer->read_char(lexer); // To advance beyond the opening '
			const char *temp = read_arg_squotes(lexer).literal;
			lexer->read_char(lexer); // To advance beyond the closing '
			ident = ft_strjoin(ident, (char *)temp);
		}
		if (lexer->ch == '\\') {
			lexer->read_char(lexer);
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		}
		else
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		lexer->read_char(lexer);
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
	if (lexer->read_position <= strlen(lexer->input))
		return (lexer->input[lexer->read_position]);
	return ('\0');
}

void expand(t_lexer *l, char *ident) {
	char *var;
	size_t ident_l;
	char *new_input;
	char *temp_sub;
	char *temp_join;

	ident_l = ft_strlen(ident) + 1;
	// TODO: to free or not to free
	// TODO: to protect or not to protect
	var = getenv(ident);
	printf("%s\n", var);
	// TODO: to free or not to free
	temp_sub = ft_substr(l->input, 0, l->position - ident_l);
	temp_join = ft_strjoin(temp_sub, var);
	free(temp_sub);
	// TODO: to free or not to free
	temp_sub = ft_substr(l->input,l->position + ident_l - 2, ft_strlen(l->input));
	new_input = ft_strjoin(temp_join, temp_sub);
	free(temp_sub);
	free(temp_join);
	printf("NEW INPUT: %s\n", new_input);
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
		if (lexer->peek_char(lexer) == ' ')
			tok = new_token(g_arg, "$");
		else
		{
			lexer->read_char(lexer);
			expand(lexer, lexer->read_arg_no_quotes(lexer));
		}
	}

	if (lexer->ch == '"') {
		// TODO: Expand
		lexer->read_char(lexer);
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
		lexer->read_char(lexer);
		tok = read_arg_squotes(lexer);
	}
	// TO THINK ABOUT: Do I need to include - as option or as argument
	// else if (lexer->ch == '-') {
	// 	if (lexer->peek_char(lexer) != ' ') {
	// 		tok.literal = "-";
	// 		tok.type = g_option;
	// 	}
	// 	else {
	// 		tok.literal = "-";
	// 		tok.type = g_arg;
	// 	}
	// }
	else if (lexer->ch == '|') {
		if (lexer->peek_char(lexer) == '|')
		{
			lexer->read_char(lexer);
			tok = new_token(g_or, "||");
		}
		else
			tok = new_token(g_pipe, "|");
	}
	else if (lexer->ch == '&') {
		if (lexer->peek_char(lexer) == '&')
		{
			tok = new_token(g_and, "&&");
			lexer->read_char(lexer);
		}
		else
			tok = new_token(g_ampersand, "&");
	}
	else if (lexer->ch == '>' && lexer->peek_char(lexer) == '>')
	{
		lexer->read_char(lexer);
		tok.literal = ">>";
		tok.type = g_a_redirection;
	}
	else if (lexer->ch == '>') {
		tok.literal = ">";
		tok.type = g_r_redirection;
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
		tok.literal = lexer->read_arg_no_quotes(lexer);
		tok.type = lookup_ident(tok.literal);
		return (tok);
	}
	lexer->read_char(lexer);
	return (tok);
}

t_token		new_token(const char *type, const char *literal)
{
	t_token tok;
	tok.literal = literal;
	tok.type = type;
	return (tok);
}

void			skip_white_spaces(t_lexer *lexer)
{
	while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' || lexer->ch == '\r')
		lexer->read_char(lexer);
}
