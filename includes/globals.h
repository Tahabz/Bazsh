#ifndef GLOBALS_H
# define GLOBALS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

extern const char	*g_illegal;
extern const char	*g_ident;
extern const char	*g_assign;
extern const char	*g_int;
extern const char	*g_plus;
extern const char	*g_comma;
extern const char	*g_semmicolon;
extern const char	*g_lparen;
extern const char	*g_rparen;
extern const char	*g_function;
extern const char	*g_let;
extern const char	*g_minus;
extern const char	*g_bang;
extern const char	*g_asterik;
extern const char	*g_slash;
extern const char	*g_lt;
extern const char	*g_gt;
extern const char	*g_true;
extern const char	*g_false;
extern const char	*g_if;
extern const char	*g_else;
extern const char	*g_return;
extern const char	*g_eq;
extern const char	*g_not_eq;
extern const char	*keys[];

extern const char *g_built_in;
extern const char *built_ins[];
extern const char *g_arg;
extern const char *g_param;
extern const char *g_option;
extern const char *g_redirection;
extern const char *g_pipe;
extern const char *g_and;
extern const char *g_or;
extern const char *g_exec;
extern const char *g_lbrace;
extern const char *g_rbrace;
extern const char *g_blash;
extern const char *g_slash;
extern const char *g_eof;
extern const char *g_dquote;
extern const char *g_squote;
extern const char *g_seperator;
extern const char *g_space;


typedef struct		s_token {
	const char *type;
	const char *literal;
}					t_token;
const char *getKeyType(const char *literal);
const char *lookup_ident(const char *literal);
#endif
