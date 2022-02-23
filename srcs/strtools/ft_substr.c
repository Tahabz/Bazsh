/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   ft_substr.c                                   000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 22:07:42 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 22:07:42 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "strtools.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;
	size_t	lens;

	if (!s)
		return (0);
	lens = ft_strlen(s);
	if (lens < start)
		len = 0;
	i = 0;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (0);
	while (i < (int)len && start < lens)
	{
		*(ptr + i) = *(s + start);
		start++;
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
