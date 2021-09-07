#include <sys/_types/_size_t.h>
#include <stdlib.h>
#include <unistd.h>

char	*char_to_string(const char ch);
char			*ft_strdup(const char *str);
char		*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
