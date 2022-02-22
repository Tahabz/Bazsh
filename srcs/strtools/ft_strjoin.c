/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   ft_strjoin.c                                  000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 22:05:10 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 22:05:10 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "strtools.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = 0;
	}
	if (!s2)
		return (ft_strdup(s1));
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (*(s1 + i) != '\0')
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	while (*(s2 + j) != '\0')
		*(ptr + i++) = *(s2 + j++);
	*(ptr + i) = '\0';
	return (ptr);
}
