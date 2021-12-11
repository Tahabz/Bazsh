#include "../srcs/parser.h"
#include <stdio.h>

int main()
{
	const t_lexer lexer = new_lexer("/bin/cat srcs/executor.c | /usr/bin/grep main | /usr/bin/wc -l");
	t_parser *    parser = parser_new(lexer);
	t_command *   command = start_parser(parser);
	// puts(command->arg->val);
	// puts(command->arg->next->val);
}
