/* ************************************************************************** */
/*                                                                            */
/*                                                 000000000000000000         */
/*   ft_split.c                                    000000000000000000         */
/*                                                 000000000000000000         */
/*   By: ael-hach <ael-hach@student.codam.nl>      000000000000000000         */
/*                                                 000000000000000000         */
/*   Created: 2022/02/22 22:14:50 by ael-hach      000000000000000000         */
/*   Updated: 2022/02/22 22:14:50 by ael-hach      000000000000000000         */
/*                                                                            */
/* ************************************************************************** */

#include "strtools.h"

static int	is_split(char str, char c)
{
	if (str == c)
		return (1);
	else
		return (0);
}

static int	word_count(const char *str, char c)
{
	int	i;
	int	output;

	i = 0;
	output = 0;
	while (str[i])
	{
		if (c != str[i] && (i == 0 || str[i - 1] == c))
		{
			output++;
			i++;
		}
		else
			i++;
	}
	return (output);
}

static int	letter_count(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (!is_split(str[i], c) && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char	*get_word(const char *str, char a, char **arr, int k)
{
	int		i;
	char	*c;

	i = 0;
	c = malloc(letter_count(str, a) + 1);
	while (!is_split(str[i], a) && *(str + i) != '\0')
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char	**ft_split(char const *str, char c)
{
	char	**array;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!str)
		return (0);
	array = malloc(sizeof(char *) * (word_count(str, c) + 1));
	while (str[i])
	{
		if (!is_split(str[i], c) && (i == 0 || is_split(str[i - 1], c)))
		{
			array[k] = get_word(&str[i], c, array, k);
			if (!array[k])
				return (0);
			k++;
		}
		i++;
	}
	array[k] = 0;
	return (array);
}
