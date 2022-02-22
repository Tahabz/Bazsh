/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   char_to_string.c                              000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 22:13:15 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 22:13:15 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "strtools.h"

/*
** CAUTION: returns a new string (heap allocated) which needs to be freed later
*/
char	*char_to_string(const char ch)
{
	char	*str;

	str = malloc(2);
	str[0] = ch;
	str[1] = '\0';
	return (str);
}
