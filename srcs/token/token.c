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

const char *lookup_ident(const char *literal)
{
	unsigned int	len;
	unsigned int	i;
	const char *built_ins[] = {
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit"
	};

	i = 0;
	len = sizeof(built_ins) / sizeof(*built_ins);
	while (i < len && literal)
	{
		if (strcmp(literal, built_ins[i]) == 0)
			return (BUILT_IN);
		i++;
	}
	return (NULL);
}
