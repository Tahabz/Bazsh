#ifndef LEXER_H
# define LEXER_H

#include "../token/token.h"
#include "../get_next_line/get_next_line.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../strtools/strtools.h"

typedef struct s_return {
	const char *data;
	const char *state;
}				t_return;

typedef struct	s_lexer {
	char			*input;
	unsigned int	position;
	unsigned int	read_position;
	char			ch;
}				t_lexer;

t_lexer						new_lexer(const char *input);
void						read_char(t_lexer *lexer);
char						peek_char(t_lexer *lexer);
void						skip_whitespace(t_lexer *lexer);
t_token						next_token(t_lexer *lexer);
t_token						new_token(const char *type, const char *literal);
t_token						read_arg_no_quotes(t_lexer *lexer);
t_token						read_arg_dquotes(t_lexer *lexer);
t_token						read_arg_squotes(t_lexer *lexer);
t_token						lex_token(t_lexer *lexer);
void						expand(t_lexer *l, const char *ident);
#endif
