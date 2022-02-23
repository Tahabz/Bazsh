/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:17:02 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/23 14:38:16 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	panic(const char *str_format, ...)
{
	va_list	args;

	va_start(args, str_format);
	printf(str_format, args);
	va_end(args);
	exit(1);
}

static void	put_error(const char *str)
{
	write(2, str, ft_strlen(str));
}

void	raise_syntax_error(const char *expected, t_parser *parser)
{
	put_error("\tSyntax Error 🙀 ✋ ⛔️ \n");
	put_error("expected\t✅ : ");
	put_error(expected);
	put_error("\n");
	put_error("found\t\t❌ : ");
	put_error(parser->peek_tok.literal);
	put_error("\n");
	parser->parsing_state = NULL;
}
