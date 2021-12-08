#include "token.h"

t_token		new_token(const char *type, const char *literal)
{
	t_token tok;
	tok.literal = ft_strdup(literal);
	tok.type = type;
	return (tok);
}

int		is_separator(const char ch)
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
