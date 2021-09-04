#include "lexer.h"
#include "token/token.h"

// TODO: Rewrite the tests
// TODO: Test for incomplete quoting mixed with args (e.g. hello'world)
int			main(void)
{
	char *input =  "hello\" world\"!; echo<<>>";
	t_lexer l = new_lexer(input);
	const t_token tests[] = {
		new_token(g_arg, "hello world!"),
		new_token(g_seperator, ";"),
		new_token(g_space, " "),
		new_token(g_built_in, "echo"),
		new_token(g_heredoc, "<<"),
		new_token(g_a_redirection, ">>"),
		new_token(g_eof, ""),
	};

	int ok = 0;
	unsigned int len = sizeof(tests) / sizeof(*tests);
	for (unsigned int i = 0; i < len; i++)
	{
		const t_token tok = next_token(&l);
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
