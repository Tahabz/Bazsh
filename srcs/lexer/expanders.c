#include "lexer.h"

void expand(t_lexer *l, const char *ident)
{
	char        *var;
	char        *new_input;
	char        *temp_sub;
	char        *temp_join;
	const size_t ident_l = ft_strlen(ident) + 1;

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
