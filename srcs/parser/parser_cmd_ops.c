/* ************************************************************************** */
/*                                                                            */
/*                                                 0000000000000000000        */
/*   parser_cmd_ops.c                              0000000000000000000        */
/*                                                 0000000000000000000        */
/*   By: ael-hach <ael-hach@student.codam.nl>      0000000000000000000        */
/*                                                 0000000000000000000        */
/*   Created: 2022/02/22 23:16:06 by ael-hach      0000000000000000000        */
/*   Updated: 2022/02/22 23:16:06 by ael-hach      0000000000000000000        */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_arg	*new_arg(const char *value)
{
	t_arg	*arg;

	arg = malloc(sizeof(*arg));
	arg->val = ft_strdup(value);
	arg->next = NULL;
	return (arg);
}

void	append_arg(t_arg **head_arg, const char *value)
{
	t_arg	*tail;

	tail = *head_arg;
	if (*head_arg == NULL)
	{
		*head_arg = new_arg(value);
		return ;
	}
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new_arg(value);
}

t_command	*create_command(void)
{
	t_command	*command;

	command = malloc(sizeof(*command));
	*command = (t_command){
		.arg = NULL,
		.in_sequence = NULL,
		.out_sequence = NULL,
		.next = NULL,
	};
	return (command);
}

void	add_io(t_io **io_head, t_io value)
{
	t_io	*new_io;
	t_io	*tail;

	tail = *io_head;
	new_io = malloc(sizeof(*new_io));
	*new_io = value;
	if (*io_head == NULL)
	{
		*io_head = new_io;
		return ;
	}
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new_io;
}
