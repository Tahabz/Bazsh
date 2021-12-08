#include "lexer.h"

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

void skip_whitespace(t_lexer *lexer)
{
	while (lexer->ch == ' ' || lexer->ch == '\t')
	{
		read_char(lexer);
	}
}
