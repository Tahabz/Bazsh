/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   ft_itoa.c                                     000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 22:14:17 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 22:14:17 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "strtools.h"

static int	ft_count(int n)
{
	unsigned int	nbr;
	int				i;

	i = 1;
	if (n < 0)
	{
		nbr = -n;
		i++;
	}
	else
		nbr = n;
	while (nbr / 10 > 0)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	char			*s;
	int				count;

	count = ft_count(n);
	s = malloc(count + 1);
	if (n == 0)
		*s = '0';
	if (n < 0)
	{
		s[0] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	s[count--] = '\0';
	while (nbr > 0)
	{
		if (count == 0 && n < 0)
			break ;
		*(s + count--) = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (s);
}
