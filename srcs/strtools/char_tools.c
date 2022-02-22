/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   char_tools.c                                  000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 22:13:34 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 22:13:34 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "strtools.h"

bool	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	else if (c >= 'A' && c <= 'Z')
		return (true);
	else if (c == '_')
		return (true);
	return (false);
}

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

bool	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i += 1;
	}
	return (true);
}
