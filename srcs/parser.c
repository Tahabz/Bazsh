#include "parser.h"

void    next_tok(t_parser *p)
{
    p->curr_tok = p->peek_tok;
    p->peek_tok = p->lexer.next_token(&p->lexer);
}

