#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int     get_next_line(int fd, char **line);
void    ft_putchar(char c);
void	ft_putstr(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup (const char *s1);
size_t	ft_strlen (const char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif