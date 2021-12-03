#include "../srcs/lexer.h"
#include "../srcs/token/token.h"
#include <stdlib.h>

int main(void)
{
	char	     *input = "hello\" world\"! echo $PWD <<>>";
	t_lexer       l = new_lexer(input);
	const t_token tests[] = {
	    new_token(ARG, "hello world!"),
	    new_token(ARG, "echo"),
	    new_token(ARG, getenv("PWD")),
	    new_token(HEREDOC, "<<"),
	    new_token(APPEND, ">>"),
	    new_token(EOF_, ""),
	};

	int          ok = 0;
	unsigned int len = sizeof(tests) / sizeof(*tests);
	for (unsigned int i = 0; i < len; i++)
	{
		const t_token tok = next_token(&l);
		if (strcmp(tok.literal, tests[i].literal) != 0)
		{
			printf("Test [%d] ERROR: Token Literal mismatch "
			       "\nExpected:'%s'\nGot\t:'%s'\n\n",
			       i, tests[i].literal, tok.literal);
			ok = 1;
		}
		if (strcmp(tok.type, tests[i].type) != 0)
		{
			printf("Test [%d] ERROR: Token Type mismatch "
			       "\nExpected:'%s'\nGot\t:'%s'\n\n",
			       i, tests[i].type, tok.type);
			ok = 1;
		}
	}
	if (ok == 0)
		printf("OK\n");
	return 0;
}
