#ifndef TOKEN_H
# define TOKEN_H
# include <string.h>
# include "../strtools/strtools.h"
# define BUILT_IN "BUILT_IN"
# define ARG "ARGUMENT"
# define VAR "VARIABLE"
# define R_REDIRECTION ">"
# define L_REDIRECTION "<"
# define APPEND ">>"
# define HEREDOC "<<"
# define PIPE "|"
# define EXEC "EXECUTABLE"
# define EOF_ "EOF"
# define SPACE " "
# define TAB "\t"
# define EQUAL "="
# define INVALID "INVALID"
# define SINGLE_Q_ARG "SINGLE_Q_ARG"
# define DOUBLE_Q_ARG "DOUBLE_D_ARG"

typedef struct		s_token {
	const char *type;
	char *literal;
}					t_token;

const char *getKeyType(const char *literal);
const char *lookup_ident(const char *literal);
int	is_separator(const char ch);

#endif
