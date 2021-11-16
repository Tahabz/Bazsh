#include "lexer.h"

typedef struct s_parser
{
	t_lexer lexer;
	t_token curr_tok;
	t_token peek_tok;
} t_parser;

enum io_type
{
	IO_STDIN,
	IO_STDOUT,
	IO_STDERR,
	IO_FILE,
	IO_PIPE
};

typedef struct s_io
{
	enum io_type type;
	char *  value;
} t_io;

typedef struct s_command
{
	char *            name;
	char **           args;
	t_io              in;
	t_io              out;
	struct s_command *next;
} t_command;

t_command *parse_command(t_parser *parser);

bool curr_tok_is(const t_parser *parser, const char *tok);
bool peek_tok_is(const t_parser *parser, const char *tok);
bool expect_peek(t_parser *parser, const char *tok);

void     next_tok(t_parser *p);
t_parser *parser_new(t_lexer l);
