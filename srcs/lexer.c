#include "globals.h"
#include "lexer.h"
#include "libft.h"

t_lexer		new_lexer(const char *input)
{
	t_lexer l;
	l.input = input;
	l.read_position = 0;
	l.position = 0;
	l.skip_white_spaces = &skip_white_spaces;
	l.peak_char = &peak_char;
	l.read_identifier = &read_identifier;
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
		if (lexer->peak_char(lexer) == '\\') {
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

char						*read_identifier(struct s_lexer *lexer)
{
	int position;
	int exist;
	char *ident;

	ident = 0;
	exist = 0;
	position = lexer->position;
	while (ft_isalpha(lexer->ch) || lexer->ch == '\\') {

		if (lexer->ch == '\\') {
			lexer->read_char(lexer);
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		}
		else if (lexer->ch == '\'' || lexer->ch == '"')
			break ;
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

char			peak_char(t_lexer *lexer)
{
	if (lexer->read_position <= strlen(lexer->input))
		return (lexer->input[lexer->read_position]);
	return ('\0');
}

t_token		next_token(t_lexer *lexer)
{
	t_token tok;
	lexer->skip_white_spaces(lexer);
	if (lexer->ch == '"') {
		tok.literal = "\"";
		tok.type = g_dquote;
		// lexer->read_char(lexer);
		// t_return ret;
		// ret = trim(lexer, '"');
		// tok.literal = ret.data;
		// tok.type = g_arg;
	}
	else if (lexer->ch == '\'') {
		tok.literal = "\'";
		tok.type = g_squote;
	}
	else if (lexer->ch == '-') {
		if (lexer->peak_char(lexer) != ' ') {
			tok.literal = "-";
			tok.type = g_option;
		}
		else {
			tok.literal = "-";
			tok.type = g_arg;
		}
	}
	else if (lexer->ch == '$') {
		if (lexer->peak_char(lexer) == ' ')
		{
			tok.literal = "$";
			tok.type = g_arg;
		}
		else
		{
			lexer->read_char(lexer);
			tok.literal = lexer->read_identifier(lexer);
			tok.type = g_param;
			return (tok);
		}
	}
	else if (lexer->ch == '|') {
		tok.literal = "|";
		tok.type = g_pipe;
	}
	else if (lexer->ch == '>' || lexer->ch == '<') {
		//TODO: must use > as string not char
		tok.literal = (lexer->ch == '>' ? ">" : "<");
		tok.type = g_redirection;
	}
	else if (lexer->ch == '\0')
		tok = new_token(g_eof, "\0");
	else {
		tok.literal = lexer->read_identifier(lexer);
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