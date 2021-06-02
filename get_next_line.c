/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.c>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 09:02:22 by jbadia            #+#    #+#             */
/*   Updated: 2021/06/02 16:21:54 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check_errors(int fd, char **line)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	return (0);
}

int	ft_ret_read(int fd, char *buff, int buff_size, int *bytes)
{
	*bytes = read(fd, buff, buff_size);
	buff[*bytes] = '\0';
	return (*bytes);
}

char 	*ft_save_line(char *str, char **line, int *bytes)
{
	unsigned int	len_of_line;
	char			*temp;

	len_of_line = 0;
	while (str[len_of_line] != '\0')
	{
		if (str[len_of_line] == '\n')
			break ;
		len_of_line++;
	}
	if (len_of_line < ft_strlen(str))
	{
		*line = ft_substr(str, 0, len_of_line);
		temp = ft_substr(str, len_of_line + 1, ft_strlen(str));
		free(str);
		str = ft_strdup(temp);
		free(temp);
	}
	else if (*bytes == 0)
	{
		*line = str;
		str = NULL;
	}
	return (str);
}

char	*ft_save_in_str(char *buff, char *str)
{
	char	*temp;

	if (str)
	{
		temp = ft_strjoin(str, buff);
		str = temp;
	}
	else
		str = ft_strdup(buff);
	return (str);
}

int	get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*str;
	int			bytes;

	if ((ft_check_errors(fd, line)) == -1)
		return (-1);
	while (ft_ret_read(fd, buff, BUFFER_SIZE, &bytes) != 0)
	{
		if (bytes == -1)
			return (-1);
		str = ft_save_in_str(buff, str);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (bytes <= 0 && !str)
	{
		*line = ft_strdup("");
		return (0);
	}
	str = ft_save_line(str, line, &bytes);
	if (bytes <= 0 && !str)
		return (0);
	return (1);
}
