#include "../srcs/parser.h"
#include <stdio.h>

int main()
{
	const t_lexer lexer = new_lexer("echo hello");
	t_parser *parser = parser_new(lexer);
	t_command  *command = start_parser(parser);
//	puts(command->arg.val);
}
