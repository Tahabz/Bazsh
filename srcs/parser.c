#include "parser.h"
#include "lexer.h"
#include "token/token.h"
#include <stdlib.h>

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
	t_command command;
	program.commands = malloc(sizeof(t_command) + 1);
	while (strcmp(parser->curr_tok.type, g_eof) != 0) {
		program.commands = append_command(program.commands, parse_command(parser));
	}
	return (program);
}

t_command parse_command(t_parser *parser) {
	t_command command;

	return (command);
}

t_command *append_command(t_command *command_list, t_command command) {
	t_command *new_command_list = malloc(sizeof(t_command));
	return (new_command_list);
}

bool curr_tok_is(const t_parser *parser, const char *tok) {
	return (ft_strncmp(parser->curr_tok.type, tok, ft_strlen(tok)) == 0);
}

bool peek_tok_is(const t_parser *parser, const char *tok) {
	return (ft_strncmp(parser->peek_tok.type, tok, ft_strlen(tok)) == 0);
}

bool expect_peek(t_parser *parser, const char *tok) {
	if (peek_tok_is(parser, tok)) {
		next_tok(parser);
		return (true);
	} else {
		return (false);
	}
}
