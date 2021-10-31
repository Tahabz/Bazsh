#include "strtools.h"
#include <stdbool.h>

bool	str_match(const char *str1, const char *str2)
{
	return (ft_strcmp(str1, str2) == 0);
}
