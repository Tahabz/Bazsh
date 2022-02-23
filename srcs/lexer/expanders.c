/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:52:23 by ael-hach          #+#    #+#             */
/*   Updated: 2022/02/23 15:48:05 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*get_ident(char *input, unsigned int index)
{
	char			*ident;
	unsigned int	end;

	end = index;
	while (!is_separator(input[end]))
	{
		end++;
	}
	ident = ft_substr(input, index, end - index);
	return (ident);
}

void	expand(t_lexer *l, const char *ident)
{
	char			*var;
	char			*new_input;
	char			*temp_sub;
	char			*temp_join;
	const size_t	ident_l = ft_strlen(ident) + 1;

	var = getenv(ident);
	temp_sub = ft_substr(l->input, 0, l->position - ident_l);
	temp_join = ft_strjoin(temp_sub, var);
	free(temp_sub);
	temp_sub = ft_substr(l->input, l->position, ft_strlen(l->input));
	new_input = ft_strjoin(temp_join, temp_sub);
	free(temp_sub);
	free(temp_join);
	free(l->input);
	l->input = new_input;
	l->position -= ident_l;
	l->read_position = l->position + 1;
	l->ch = l->input[l->position];
}

void	expand_quoted(t_lexer *l)
{
	char	*ident;

	read_char(l);
	ident = get_ident(l->input, l->position);
	l->position += ft_strlen(ident);
	expand(l, ident);
	free(ident);
}
