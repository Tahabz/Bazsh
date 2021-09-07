#include "strtools.h"

static char		*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

char			*ft_strdup(const char *str)
{
	char *dst;

	dst = malloc(ft_strlen(str) + 1);
	if (dst)
		ft_strcpy(dst, str);
	return (dst);
}
