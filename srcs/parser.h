#include "lexer.h"

typedef struct s_parser {
    t_lexer lexer;
    t_token curr_tok;
    t_token peek_tok;
} t_parser;

typedef struct s_command {
    char *args;
    const char *command_type;
    const char *prev_delim;
    const char *next_delim;
} t_command;

typedef struct s_program {
    t_command *commands;
} t_program;

bool curr_tok_is(const char *tok);
bool peek_tok_is(const char *tok);
bool expect_peek(const char *tok);

void next_tok(t_parser *p);
t_parser parser_new(t_lexer l) {
    t_parser p = {l, {NULL, NULL}, {NULL, NULL}};
    next_tok(&p);
    next_tok(&p);
}

