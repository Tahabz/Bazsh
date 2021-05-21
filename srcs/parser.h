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

t_program parse_program(t_parser *parser);
t_command parse_command(t_parser *parser);

bool curr_tok_is(const t_parser *parser, const char *tok);
bool peek_tok_is(const t_parser *parser, const char *tok);
bool expect_peek(t_parser *parser, const char *tok);

void next_tok(t_parser *p);
t_parser parser_new(t_lexer l);
