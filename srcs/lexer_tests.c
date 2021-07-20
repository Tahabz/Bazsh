#include "lexer.h"
#include "token/token.h"

// TODO: Rewrite the tests
int			main(void)
{
	int ok = 0;
	t_token tok;
	char *input =  "hello\" world\"!";
	t_token tests[] = {g_arg, "hello world!"};
	t_lexer l = new_lexer(input);
	unsigned int len = sizeof(tests) / sizeof(*tests);
	for (unsigned int i = 0; i < len; i++)
	{
		tok = next_token(&l);
		if (strcmp(tok.literal, tests[i].literal) != 0) {
			printf("Test [%d] ERROR: Token Literal mismatch \nExpected:'%s'\nGot\t:'%s'\n\n", i, tests[i].literal, tok.literal);
			ok = 1;
		}
		if (strcmp(tok.type, tests[i].type) != 0) {
			printf("Test [%d] ERROR: Token Type mismatch \nExpected:'%s'\nGot\t:'%s'\n\n", i, tests[i].type, tok.type);
			ok = 1;
		}
	}
	if (ok == 0)
		printf("OK\n");
	return 0;
}
