#include "token.h"
#include <stdio.h>


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
	while (i < len && literal)
	{
		if (strcmp(literal, built_ins[i]) == 0)
			return (g_built_in);
		i++;
	}
	return (g_arg);
}
