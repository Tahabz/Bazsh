/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   parser_error.c                                000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 23:17:02 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/23 13:46:43 by ael-hach         ###   ########.fr       */
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

void	raise_syntax_error(const char *expected, t_parser *parser,
						t_command *command)
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
