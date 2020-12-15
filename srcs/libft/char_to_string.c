#include "libft.h"

char	*char_to_string(const char ch)
{
	char *str;

	str = malloc(2);
	str[0] = ch;
	str[1] = '\0';
	return (str);
}
