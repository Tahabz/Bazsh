#ifndef STRTOOLS_H
#define STRTOOLS_H
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

char * char_to_string(const char ch);
char * ft_strdup(const char *str);
char * ft_strjoin(char *s1, char *s2);
size_t ft_strlen(const char *s);
char * ft_substr(char const *s, unsigned int start, size_t len);
void   ft_putstr_fd(char *s, int fd);
int    ft_strcmp(const char *s1, const char *s2);
bool   str_match(const char *str1, const char *str2);
char **ft_split(char const *str, char c);
char * ft_itoa(int n);
bool   ft_isalpha(int c);
bool   ft_isalnum(int c);
bool   ft_isdigit(int c);
bool   ft_isnum(char *str);

#endif
