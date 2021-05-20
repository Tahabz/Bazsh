#ifndef LEXER_H
# define LEXER_H

#include "token/token.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_return {
	const char *data;
	const char *state;
}				t_return;

typedef struct	s_lexer {
	const char		*input;
	unsigned int	position;
	unsigned int	read_position;
	char					ch;
	void					(*read_char)(struct s_lexer *);
	t_token					(*next_token)(struct s_lexer *);
	void					(*skip_white_spaces)(struct s_lexer *);
	char					(*peek_char)(struct s_lexer *);
	t_token					(*read_arg_dquotes)(struct s_lexer *);
	t_token					(*read_arg_squotes)(struct s_lexer *);
	char					*(*read_arg_no_quotes)(struct s_lexer *);
	char					*(*read_number)(struct s_lexer *);
	t_return				(*trim)(struct s_lexer *, const char delim);
}				t_lexer;

t_return					trim(t_lexer *lexer, const char delim);
void						read_char(t_lexer *lexer);
t_token						next_token(t_lexer *lexer);
void						skip_white_spaces(t_lexer *lexer);
t_token						new_token(const char *type, const char *literal);
t_lexer						new_lexer(const char *input);
char						peek_char(t_lexer *lexer);
char						*read_number(t_lexer *lexer);
char						*read_arg_no_quotes(t_lexer *lexer);
t_token						read_arg_dquotes(t_lexer *lexer);
t_token						read_arg_squotes(t_lexer *lexer);
#endif
