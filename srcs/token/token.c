#include "globals.h"

const char *keys[]			= {
	"let",
	"fn",
	"true",
	"false",
	"if",
	"else",
	"return"
};

const char *built_ins[]		= {
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit"
};

const char *g_built_in = "BUILT_IN";
const char *g_arg = "ARGUMENT";
const char *g_param = "PARAMETER";
const char *g_option = "OPTION";
const char *g_redirection = "REDIRECTION";
const char *g_pipe = "|";
const char *g_and = "&&";
const char *g_or = "||";
const char *g_exec = "EXECUTABLE";
const char *g_lbrace = "{";
const char *g_rbrace = "}";
const char *g_blash = "\\";
const char *g_slash = "/";
const char *g_eof = "EOF";
const char *g_dquote = "\"";
const char *g_squote = "\'";

// const char *get_key_type(const char *literal) {
// 	if (strcmp(literal, "echo") == 0)
// 		return (g_echo);
// 	else if (strcmp(literal, "cd") == 0)
// 		return (g_cd);
// 	else if (strcmp(literal, "pwd") == 0)
// 		return (g_pwd);
// 	else if (strcmp(literal, "unset") == 0)
// 		return (g_unset);
// 	else if (strcmp(literal, "env") == 0)
// 		return (g_env);
// 	else if (strcmp(literal, "exit") == 0)
// 		return (g_exit);
// 	else if (strcmp(literal, "export") == 0)
// 		return (g_export);
// 	return (g_return);
// }

const char *lookup_ident(const char *literal)
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = sizeof(built_ins) / sizeof(*built_ins);
	while (i < len)
	{
		if (strcmp(literal, built_ins[i]) == 0)
			return (g_built_in);
		i++;
	}
	return (g_arg);
}
