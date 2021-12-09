/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:29:12 by hdo-minh          #+#    #+#             */
/*   Updated: 2021/12/09 11:29:18 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_get_linesize(t_gnlist *list)
{
	size_t		size;
	size_t		index;
	t_gnlist	*current;

	size = 0;
	current = list;
	while (current)
	{
		index = 0;
		while (current->content[index])
		{
			index++;
			size++;
		}
		current = current->next;
	}
	return (size);
}

static void	ft_fill_list(t_gnl *gnl, t_gnlist **list, t_bool *flag, int fd)
{
	while (gnl->index < BUFFER_SIZE
		&& gnl->buf[gnl->index] && gnl->buf[gnl->index] != '\n')
		gnl->index++;
	if (gnl->index < BUFFER_SIZE && gnl->buf[gnl->index] == '\n')
	{
		ft_gnlstnew(list, gnl->buf, gnl->start, gnl->index);
		gnl->index++;
		gnl->start = gnl->index;
		*flag = 0;
	}
	else if (((gnl->index < BUFFER_SIZE) && !(gnl->buf[gnl->index]))
		|| (gnl->index == BUFFER_SIZE))
	{
		ft_gnlstnew(list, gnl->buf, gnl->start, gnl->index);
		ft_memset(gnl->buf, 0, gnl->index);
		if (!read(fd, gnl->buf, BUFFER_SIZE))
			*flag = 0;
		gnl->index = 0;
		gnl->start = 0;
	}
}

static char	*ft_get_line(t_gnlist *list)
{
	t_gnlist	*current;
	size_t		i;
	size_t		j;
	char		*line;

	line = malloc((sizeof(char) * ft_get_linesize(list) + 1));
	if (!line)
		return (NULL);
	i = 0;
	current = list;
	while (current)
	{
		j = 0;
		while (current->content[j])
			line[i++] = current->content[j++];
		current = current->next;
	}
	line[i] = '\0';
	ft_gnlstclear(&list, &free);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {};
	t_bool			flag;
	t_gnlist		*list;
	char			*line;

	flag = 1;
	if (!(gnl.buf[0]) && (read(fd, gnl.buf, BUFFER_SIZE) <= 0))
		return (NULL);
	list = NULL;
	while (flag)
		ft_fill_list(&gnl, &list, &flag, fd);
	line = ft_get_line(list);
	if (!line || !(*line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
