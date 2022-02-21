#include "lexer.h"

t_lexer new_lexer(const char *input)
{
	t_lexer l;

	l.input = ft_strdup(input);
	l.read_position = 0;
	l.position = 0;
	read_char(&l);
	return (l);
}

t_token new_token(const char *type, const char *literal)
{
	t_token tok;
	tok.literal = ft_strdup(literal);
	tok.type = type;
	return (tok);
}

t_token next_token(t_lexer *lexer)
{
	t_token tok;

	skip_whitespace(lexer);
	if (lexer->ch == '$')
	{
		if (is_separator(peek_char(lexer)))
		{
			tok = new_token(ARG, "$");
			read_char(lexer);
			return (tok);
		}
		else if (peek_char(lexer) == '?')
		{
			tok = new_token(ARG, "?");
			read_char(lexer);
			read_char(lexer);
			return (tok);
		}
		else
		{
			read_char(lexer);
			t_token ident_tok = read_arg_no_quotes(lexer);
			if (ft_strcmp(ident_tok.type, INVALID) != 0)
				expand(lexer, ident_tok.literal);
			free(ident_tok.literal);
		}
	}
	return (lex_token(lexer));
}
