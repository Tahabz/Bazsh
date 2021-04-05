#include "lexer.h"
#include "token/token.h"

t_lexer		new_lexer(const char *input)
{
	t_lexer l;
	l.input = input;
	l.read_position = 0;
	l.position = 0;
	l.skip_white_spaces = &skip_white_spaces;
	l.peak_char = &peak_char;
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

char						*read_arg_squotes(t_lexer *lexer)
{
	int position;

	position = lexer->position;
	while (lexer->ch != '\'' && lexer->ch != '\0')
		lexer->read_char(lexer);
	return (ft_substr(lexer->input, position, lexer->position - position));
}

bool						escapable(char c)
{
	const size_t n_escapables = 5;
	const char escapables[n_escapables] = {'$', '\\', '"', '*', '@'};
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

char						*read_arg_dquotes(t_lexer *lexer)
{
	char *ident;

	ident = 0;
	while (lexer->ch != '\0')
	{
		if (lexer->ch == '\\' && escapable(lexer->peak_char(lexer))) {
			lexer->read_char(lexer);
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		}
		else if (lexer->ch == '\"')
			break ;
		else
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		lexer->read_char(lexer);
	}
	return (ident);
}

int		is_seperator(const char ch)
{
	if (ch == '|' || ch == '&' || ch == ';')
		return (1);
	return (0);
}

char						*read_arg_no_quotes(t_lexer *lexer)
{
	char *ident;

	ident = 0;
	while (lexer->ch != '\0' && lexer->ch != ' ' && lexer->ch != '=')
	{
		if (lexer->ch == '\\') {
			lexer->read_char(lexer);
			ident = ft_strjoin(ident, char_to_string(lexer->ch));
		}
		else if (is_seperator(lexer->ch))
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
	if (lexer->ch == '"') {
		lexer->read_char(lexer);
		tok.literal = read_arg_dquotes(lexer);
		tok.type = lookup_ident(tok.literal);
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
	else if (lexer->ch == '\'') {
		lexer->read_char(lexer);
		tok.literal = read_arg_squotes(lexer);
		tok.type = g_arg;
	}
	// TO THINK ABOUT: Do I need to include - as option or as argument
	// else if (lexer->ch == '-') {
	// 	if (lexer->peak_char(lexer) != ' ') {
	// 		tok.literal = "-";
	// 		tok.type = g_option;
	// 	}
	// 	else {
	// 		tok.literal = "-";
	// 		tok.type = g_arg;
	// 	}
	// }
	else if (lexer->ch == '$') {
		// TODO: the behavior of params inside dbl quotes is a little different without them; when escaping a char
		if (lexer->peak_char(lexer) == ' ')
			tok = new_token(g_arg, "$");
		else
		{
			lexer->read_char(lexer);
			tok.literal = lexer->read_arg_no_quotes(lexer);
			tok.type = g_variable;
			return (tok);
		}
	}
	else if (lexer->ch == '|') {
		if (lexer->peak_char(lexer) == '|')
		{
			lexer->read_char(lexer);
			tok = new_token(g_or, "||");
		}
		else
			tok = new_token(g_pipe, "|");
	}
	else if (lexer->ch == '&') {
		if (lexer->peak_char(lexer) == '&')
		{
			tok = new_token(g_and, "&&");
			lexer->read_char(lexer);
		}
		else
			tok = new_token(g_ampersand, "&");
	}
	else if (lexer->ch == '>' || lexer->ch == '<') {
		//TODO: must use > as string not char
		tok.literal = (lexer->ch == '>' ? ">" : "<");
		tok.type = g_redirection;
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
