/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:51:24 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/22 21:51:56 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "../strtools/strtools.h"
# define ARG "ARGUMENT"
# define R_REDIRECTION ">"
# define L_REDIRECTION "<"
# define APPEND ">>"
# define HEREDOC "<<"
# define PIPE "|"
# define EOF_ "EOF"
# define INVALID "INVALID"

typedef struct s_token {
	const char	*type;
	char		*literal;
}	t_token;

typedef struct s_return {
	const char	*data;
	const char	*state;
}	t_return;

typedef struct s_lexer {
	char			*input;
	unsigned int	position;
	unsigned int	read_position;
	char			ch;
}	t_lexer;

t_lexer	new_lexer(const char *input);
void	read_char(t_lexer *lexer);
char	peek_char(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);
int		is_separator(const char ch);
t_token	next_token(t_lexer *lexer);
t_token	new_token(const char *type, const char *literal);
t_token	read_arg_no_quotes(t_lexer *lexer);
t_token	read_arg_dquotes(t_lexer *l);
t_token	read_arg_squotes(t_lexer *lexer);
t_token	lex_token(t_lexer *lexer);
void	expand(t_lexer *l, const char *ident);
void	expand_quoted(t_lexer *l);
#endif
