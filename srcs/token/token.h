#ifndef TOKEN_H
#define TOKEN_H
#include <string.h>

typedef struct		s_token {
	const char *type;
	const char *literal;
}					t_token;

const char *getKeyType(const char *literal);
const char *lookup_ident(const char *literal);

static const char *g_built_in = "BUILT_IN";
static const char *g_arg = "ARGUMENT";
static const char *g_variable = "VARIABLE";
static const char *g_option = "OPTION";
static const char *g_redirection = "REDIRECTION";
static const char *g_pipe = "|";
static const char *g_and = "&&";
static const char *g_ampersand = "&";
static const char *g_exec = "EXECUTABLE";
static const char *g_lbrace = "{";
static const char *g_rbrace = "}";
static const char *g_blash = "\\";
static const char *g_slash = "/";
static const char *g_eof = "EOF";
static const char *g_dquote = "\"";
static const char *g_squote = "\'";
static const char *g_seperator = ";";
static const char *g_space = " ";
static const char *g_or = "||";
static const char *g_equal = "=";

static const char *built_ins[]		= {
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit"
};
#endif
