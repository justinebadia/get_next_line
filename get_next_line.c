/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.c>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 11:42:50 by jbadia            #+#    #+#             */
/*   Updated: 2021/05/13 11:42:56 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write (1, &str[i], 1);
		i++;
	}
}

int get_next_line(int fd, char **line)
{
    int     ret_read; //stocke le retour de read, le nbr de bytes lus ou -1 si erreur, la position du char actuel
    char    buff[BUFFER_SIZE + 1]; //stock dans buff ce que je vais lire
    char    c;
    int     len_of_line;

    len_of_line = 0;
    
    ret_read = read(fd, buff, BUFFER_SIZE);
    buff[ret_read] = '\0';
    while (buff[len_of_line] != '\n')
        len_of_line++;
    printf("%d", len_of_line);
    // while ((ret_read = read(fd, buff, BUFFER_SIZE)) != '\0')
    // {

    //     ft_putstr(buff);
    // }
    return(ret_read);
}

int main (void)
{
    int fd;
    char **line;

    line = NULL;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        ft_putstr("erreur");
        return (1);
    }
    else    
        ft_putstr("ouvert");
    get_next_line(fd, line);
    close(fd);
  
}
