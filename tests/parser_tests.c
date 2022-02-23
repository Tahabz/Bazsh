#include "../srcs/parser/parser.h"
#include <stdio.h>

int main()
{
	const t_lexer lexer = new_lexer("<file1 echo hello |\t cat | hello > test.c arg2 >> test2.c > test3.c < inputfile << delim < inputfile2 arg3 << delim2");
	t_parser *parser = parser_new(lexer);
	t_command  *command = start_parser(parser);
	puts(command->arg->val);
	puts(command->arg->next->val);
	delete_parser(parser);
	delete_command(command);
}
