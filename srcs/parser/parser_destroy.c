/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   parser_destroy.c                              000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 23:16:38 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 23:16:38 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	delete_parser(t_parser *p)
{
	if (p->curr_tok.literal)
		free(p->curr_tok.literal);
	if (p->peek_tok.literal)
		free(p->peek_tok.literal);
	free(p);
}

void	delete_args(t_arg *head)
{
	t_arg	*current;

	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}
}

void	delete_io(t_io *head)
{
	t_io	*current;

	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}
}

void	delete_command(t_command *head)
{
	t_command	*current;

	while (head)
	{
		current = head;
		head = head->next;
		delete_args(current->arg);
		delete_io(current->out_sequence);
		delete_io(current->in_sequence);
		free(current);
	}
}
