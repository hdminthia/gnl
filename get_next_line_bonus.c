/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:46:09 by hdo-minh          #+#    #+#             */
/*   Updated: 2021/12/09 11:51:16 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_line(int line_pos, char **tmp)
{
	char	*line;
	char	*new;

	if (line_pos <= 0)
	{
		if (**tmp == '\0')
		{
			free (*tmp);
			*tmp = NULL;
			return (NULL);
		}
		line = *tmp;
		*tmp = NULL;
		return (line);
	}
	new = ft_substr(*tmp, line_pos, BUFFER_SIZE);
	line = *tmp;
	line[line_pos] = 0;
	*tmp = new;
	return (line);
}

static char	*ft_read(int fd, char *content, char **tmp)
{
	ssize_t	read_value;
	char	*line;
	char	*new;

	line = ft_strchr(*tmp, '\n');
	while (!line)
	{
		read_value = read(fd, content, BUFFER_SIZE);
		if (read_value <= 0)
			return (ft_get_line(read_value, tmp));
		content[read_value] = '\0';
		new = ft_strjoin(*tmp, content);
		free(*tmp);
		*tmp = new;
		line = ft_strchr(*tmp, '\n');
	}
	return (ft_get_line(line - *tmp + 1, tmp));
}

char	*get_next_line(int fd)
{
	char		*content;
	char		*buff;
	static char	*tmp[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!tmp[fd])
		tmp[fd] = ft_strdup("");
	content = ft_read(fd, buff, &tmp[fd]);
	if (buff != NULL)
	{
		free (buff);
		buff = NULL;
	}
	return (content);
}
