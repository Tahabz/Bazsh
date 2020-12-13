#include "globals.h"
#include "lexer.h"

int			main(void)
{
	int ok = 0;
	t_token tok;
	const char *input =  "let five = 5;\
	let ten = 10;\
	   let add = fn(x, y) {\
		 x + y;\
	};\
	   let result = add(five, ten);\
	   !-/*5;\
	   5 < 10 > 5;\
	   if (5 < 10) {\
		   return true;\
	   } else {\
		   return false;\
		10 == 10; 10 != 9;\
	}";
	t_token tests[] = {
		{g_let, "let"},
		{g_ident, "five"},
		{g_assign, "="},
		{g_int, "5"},
		{g_semmicolon, ";"},
		{g_let, "let"},
		{g_ident, "ten"},
		{g_assign, "="},
		{g_int, "10"},
		{g_semmicolon, ";"},
		{g_let, "let"},
		{g_ident, "add"},
		{g_assign, "="},
		{g_function, "fn"},
		{g_lparen, "("},
		{g_ident, "x"},
		{g_comma, ","},
		{g_ident, "y"},
		{g_rparen, ")"},
		{g_lbrace, "{"},
		{g_ident, "x"},
		{g_plus, "+"},
		{g_ident, "y"},
		{g_semmicolon, ";"},
		{g_rbrace, "}"},
		{g_semmicolon, ";"},
		{g_let, "let"},
		{g_ident, "result"},
		{g_assign, "="},
		{g_ident, "add"},
		{g_lparen, "("},
		{g_ident, "five"},
		{g_comma, ","},
		{g_ident, "ten"},
		{g_rparen, ")"},
		{g_semmicolon, ";"},
		{g_bang, "!"},
		{g_minus, "-"},
		{g_slash, "/"},
		{g_asterik, "*"},
		{g_int, "5"},
		{g_semmicolon, ";"},
		{g_int, "5"},
		{g_lt, "<"},
		{g_int, "10"},
		{g_gt, ">"},
		{g_int, "5"},
		{g_semmicolon, ";"},
		{g_if, "if"},
		{g_lparen, "("},
		{g_int, "5"},
		{g_lt, "<"},
		{g_int, "10"},
		{g_rparen, ")"},
		{g_lbrace, "{"},
		{g_return, "return"},
		{g_true, "true"},
		{g_semmicolon, ";"},
		{g_rbrace, "}"},
		{g_else, "else"},
		{g_lbrace, "{"},
		{g_return, "return"},
		{g_false, "false"},
		{g_semmicolon, ";"},
		{g_int, "10"},
		{g_eq, "=="},
		{g_int, "10"},
		{g_semmicolon, ";"},
		{g_int, "10"},
		{g_not_eq, "!="},
		{g_int, "9"},
		{g_semmicolon, ";"},
		{g_rbrace, "}"},
		{g_eof, ""},
	};
	l = new(input);
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
	return 1;
}