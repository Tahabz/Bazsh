#include "parser.h"

t_parser parser_new(t_lexer l) {
    t_parser p = {l, {NULL, NULL}, {NULL, NULL}};
    next_tok(&p);
    next_tok(&p);
	return (p);
}

void    next_tok(t_parser *p)
{
    p->curr_tok = p->peek_tok;
    p->peek_tok = p->lexer.next_token(&p->lexer);
}

t_program parse_program(t_parser *parser) {
	t_program program;

	return (program);
}

t_command parse_command(t_parser *parser) {
	t_command command;

	return (command);
}

bool curr_tok_is(const t_parser *parser, const char *tok) {
	return (ft_strncmp(parser->curr_tok.type, tok, ft_strlen(tok)));
}

bool peek_tok_is(const t_parser *parser, const char *tok) {
	return (ft_strncmp(parser->peek_tok.type, tok, ft_strlen(tok)));
}

bool expect_peek(t_parser *parser, const char *tok) {
	if (peek_tok_is(parser, tok)) {
		next_tok(parser);
		return (true);
	} else {
		return (false);
	}
}
