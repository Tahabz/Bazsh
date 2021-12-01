#ifndef TOKEN_H
# define TOKEN_H
# include <string.h>
# include "../strtools/strtools.h"
# define ARG "ARGUMENT"
# define R_REDIRECTION ">"
# define L_REDIRECTION "<"
# define APPEND ">>"
# define HEREDOC "<<"
# define PIPE "|"
# define EOF_ "EOF"
# define SPACE " "
# define TAB "\t"
# define EQUAL "="
# define INVALID "INVALID"

typedef struct		s_token {
	const char *type;
	char *literal;
}					t_token;

const char *getKeyType(const char *literal);
int	is_separator(const char ch);

#endif
