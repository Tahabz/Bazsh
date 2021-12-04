#include "lexer.h"

typedef struct s_parser t_parser;
typedef struct s_command t_command;
typedef void t_parsing_state(t_parser *parser, t_command *cmd);

typedef struct s_parser
{
	t_lexer lexer;
	t_token curr_tok;
	t_token peek_tok;
	t_parsing_state *parsing_state;
} t_parser;

enum io_type
{
	IO_STDIN,
	IO_STDOUT,
	IO_STDERR,
	IO_FILE,
	IO_FILE_APPEND,
	IO_FILE_HEREDOC,
	IO_PIPE
};

typedef struct s_io
{
	enum io_type type;
	char *       value;
	struct s_io *next;
} t_io;

typedef struct s_arg
{
	char *        val;
	struct s_arg *next;
} t_arg;

typedef struct s_command
{
	t_arg             *arg;
	t_io              in;
	t_io              *out_sequence;
	struct s_command *next;
} t_command;

t_command *parse_command(t_parser *parser);
t_command *start_parser(t_parser *parser);

bool curr_tok_is(const t_parser *parser, const char *tok);
bool peek_tok_is(const t_parser *parser, const char *tok);
bool expect_peek(t_parser *parser, const char *tok);
void parse_arg(t_parser *parser, t_command *cmd);
void parse_pipe(t_parser *parser, t_command *cmd);
void parse_out_redirect(t_parser *parser, t_command *cmd);

void      next_tok(t_parser *p);
t_parser *parser_new(t_lexer l);
