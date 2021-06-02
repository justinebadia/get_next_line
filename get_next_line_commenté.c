#include "get_next_line.h"
#include <stdio.h>


int ft_ret_read(int fd, char *buff, int buff_size, int *bytes)
{
    *bytes = read(fd, buff, buff_size);
    buff[*bytes] = '\0';
    return (*bytes);
}

char  *ft_save_line(char *str, char **line, int *bytes)
{
    unsigned int     len_of_line;
    char    *temp;

    len_of_line = 0;
    while (str[len_of_line] != '\0')
    {
        if (str[len_of_line] == '\n')
            break ;
        len_of_line++; // soit line s'arrête sur un \n, soit à la longueur du buffersize
    }
    if (len_of_line < ft_strlen(str)) // si inférieur, c'est que j'ai un \n dans str
    {
        *line = ft_substr(str, 0, len_of_line); //j'enregistre dans line le morceau de str du début jusq'au \n
        temp = ft_substr(str, len_of_line + 1, ft_strlen(str)); // dans la temp, j'enregistre, le morceau de str après le \n
        free(str);
        str = ft_strdup(temp); //je donne à str sa nouvelle adresse, sans le premier morceau de phrase
        free(temp);
    }
    else if (*bytes == 0) //si je suis en fin de fichier
    {
        *line = str; //je donne à a line l'adresse de str qui est vide
        str = NULL; // je remets str à 0
    }
    return (str); 
}

//si j'ai qqch dans str, je join mon morceau de str et le buff
//sinon, je copie le buff directement dans str
char    *ft_save_in_str(char *buff, char *str)
{
    char *temp;
    if (str) 
    {
        temp = ft_strjoin(str, buff); //str est free dans strjoin
        str = temp;
    }
    else // pour le premier passage, je copie tout le buff dans str
        str = ft_strdup(buff);
    return (str);

}

int ft_check_errors(int fd, char **buff, char **line)
{
   
    
    if (fd < 0 || BUFFER_SIZE <= 0 || !line)
    {
    printf("FD :%p\n", &fd);
    printf("buff :%p\n", buff);
    printf("line :%p\n", line);
        return (-1); 
    }
        
    *buff = (char *)malloc(sizeof (char) * BUFFER_SIZE + 1);
    if (*buff == NULL)
    {
        free(*buff);
        return(-1);
    }
    


    return (0);             
}

int     get_next_line(int fd, char **line)
{
    char                *buff;
    static char         *str;
    int                 bytes;

     buff = NULL;
    if ((ft_check_errors(fd, &buff, line)) == -1)
        return(-1);
    while (ft_ret_read(fd, buff, BUFFER_SIZE, &bytes) != 0) // tant que que je ne suis pas à EOF
    {
         if (bytes == -1)
            return (-1);
        str = ft_save_in_str(buff, str); //je join mon buff à la suite de str
        if (ft_strchr(buff, '\n')) //si je trouve un \n, je sors
            break ;
    }
    free(buff);
    if (bytes <= 0 && !str) // si on passe un fichier vide, je strdup rien dans line
    { 
        *line = ft_strdup("");
        return (0);
    }
    str = ft_save_line(str, line, &bytes); // fonction qui enregistre la phrase dans line
    if (bytes <= 0 && !str) // en EOF bytes == 0 et str est NULL
        return (0);
    return (1); // 1 car ma phrase est enregistrée dans ligne
}


int main (void)
{
    int fd = -1;
    char *line;
    line = NULL;

    
    while (get_next_line(fd, &line) > 0)
    {
        printf("%s\n", line);
        //free(line);
    }
    printf("%s\n", line);

    close(fd);
    return (0);
}
