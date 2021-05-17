/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 11:42:50 by jbadia            #+#    #+#             */
/*   Updated: 2021/05/16 16:07:18 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static int  ft_check_eol(char *s)
{
    int i;
    while (s[i] != '\n')
    {
        if(s[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

static int  ft_save_line(char **line, char **buffer)
{
    char    *temp;
    char    *temp_join_line;
    char    *temp_buff;
    int     len;

    len = ft_check_eol(*buffer);
    if (len >= 0) // ca veut dire que j'ai rencontré un \n dans mon buffer
    {
        temp = ft_substr(buffer, 0, len - 1); // je copie la premiere ligne dans temp sans le \n
        temp_join_line = *line; // je save la valeur actuelle de line dans temp_
        *line = ft_strjoin(*line, temp); // je join la phrase précédente à la nouvelle phrase qui est dans temp
        temp_buff = ft_strdup(buffer[len + 1]);
        buffer = &temp_buff; //je donne à buffer une chaine dupliquée sans la ligne qu,on vient d,enregistrer dans line
        free(temp);
        free(temp_join_line);
        free(temp_buff);
        return (1); // je suis arrivée en fin de ligne
    }
    else // pas de \n dans mon buffer
    {
        temp = NULL;
        temp = *line;
        *line = ft_strjoin(*line, *buffer);
        free (temp);
    }
}

//save line permets de lire jusqu'au \n puis de passer à la ligne suivante : ligne par ligne
static int  ft_save_line(char **s, char **line)
{
    char *temp;
    int len_of_line;

    temp = NULL;
    len_of_line = 0;
    while ((*s)[len_of_line] != '\n' && (*s)[len_of_line] != '\0') // calcul la longueur de la ligne
        len_of_line++;
    if ((*s)[len_of_line] == '\n')
    {
        *line = ft_substr(*s, 0, len_of_line); // j'enregistre la première ligne dans *line
        temp = ft_strdup(s[len_of_line + 1]); // j'enregistre dans temp la chaine s juste après là ou j'ai copié dans line, juste la ligne d'après
        free (s); // je remets *s à 0
        s = &temp; // je donne à s son nouveau texte, sans la ligne précédente
    }
    else // si je ne trouve pas de \n 
    {
        *line = ft_strdup(*s); // j'alloue et je copie s dans line
                                // je join mes morceaux de lignes puis quand je vais rencontre le \n, je passe dans le if
    }
    return (1); // ligne lue = return 1 ou si je retourne line pour avoir un pointeur vers la copie ?
}

int     get_next_line(int fd, char **line)
{
    char                *buff;
    static char        **str;
    int             ret_read;
    
    buff = NULL;
    line = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 || !line)
        return (-1);
    buff = (char *)malloc(sizeof (char) * BUFFER_SIZE + 1);
    if (buff == NULL)
        return (-1);
    ret_read = read (fd, buff, BUFFER_SIZE);
    if (ret_read == -1)
        return (-1);
    buff[ret_read] = '\0';

   while ()// tant que je ne suis pas à la fin de mon fichier et tant que je ne suis pas à la fin de ma ligne, j'enregistre mon buff dans la line, ligne par ligne (créer une fonction)
   {
       //lire le fichier
        //je fais un strjoin tant que je n'atteint pas un \n ou \0    
   }
    
    if (ret_read == 0)
        return (0);
    // puis je fais un join pour lier les chaines, je le stocke dans s
}

// int get_next_line(int fd, char **line)
// {
//     int     ret_read; //stocke le retour de read, le nbr de bytes lus ou -1 si erreur, la position du char actuel
//     char    buff[BUFFER_SIZE + 1]; //stock dans buff ce que je vais lire
//     char    c;
//     int     len_of_line;
//     char    **save;
//     int     i;

//     len_of_line = 0;
//     i = 0;
    
//     ret_read = read(fd, buff, BUFFER_SIZE); // stocke le retour de read, le nombre de bytes lus
//     buff[ret_read] = '\0';
//     while (buff[len_of_line] != '\n')
//     {
//         ft_putchar(buff[len_of_line]);
//         len_of_line++;
//     }
//     printf("%d", len_of_line);

//     return(ret_read);
// }

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
