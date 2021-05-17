#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


static int  ft_check_eol(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

// static int  ft_save_line(char *buff, char **line, char **str)
// {
//     int     len_of_line;
//     char    *temp;

//     if (len_of_line > 0)
//     {
//         *line = ft_substr(buff, 0, len_of_line); 
//         *str = ft_substr(buff, len_of_line + 1, ft_strlen(buff) - len_of_line);
//         free(buff);
//     }
//     else
//     {

//     }

// }

static void ft_save_line(char *str, char **line)
{
    int i;

    i = ft_check_eol(str);
    *line = (char *)malloc(sizeof(char) * i + 1);
    if (line == NULL)
        return (NULL);
    while (i > 0)
    {
        *line[i] = str[i];
        i--;
    }

}

int     get_next_line(int fd, char **line)
{
    char                *buff;
    static char        **str;
    int             ret_read;

    ret_read = 1;
    if (fd < 0 || BUFFER_SIZE <= 0 || !line)
        return (-1);
    buff = (char *)malloc(sizeof (char) * BUFFER_SIZE + 1);
    if (buff == NULL)
        return (-1);
    while (!ft_strchr(buff, '\n') || ret_read > 0)
    {
        ret_read = read (fd, buff, BUFFER_SIZE);
       
        if (ret_read == -1)
        {
            free(buff);
            return (-1);
        }
        buff[ret_read] = '\0';
        str = ft_strjoin(str, buff);
        
    }
    free(buff);
    ft_save_line(str, &*line);
}