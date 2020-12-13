#ifndef LEXER_H
# define LEXER_H

typedef struct	s_lexer {
	const char		*input;
	unsigned int	position;
	unsigned int	read_position;
	char					ch;
	void					(*read_char)(struct s_lexer *);
	t_token					(*next_token)(struct s_lexer *);
	void					(*skip_white_spaces)(struct s_lexer *);
	char					(*peak_char)(struct s_lexer *);
	char					*(*read_identifier)(struct s_lexer *);
	char					*(*read_number)(struct s_lexer *);
}				t_lexer;
t_lexer					l;
typedef struct s_return {
	const char *data;
	const char *state;
}				t_return;

void						read_char(t_lexer *lexer);
t_token						next_token(t_lexer *lexer);
void						skip_white_spaces(t_lexer *lexer);
t_token						new_token(const char *type, const char *literal);
t_lexer						new_lexer(const char *input);
char						peak_char(t_lexer *lexer);
char						*read_identifier(struct s_lexer *lexer);
char						*read_number(t_lexer *lexer);
#endif