/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:11:05 by hdo-minh          #+#    #+#             */
/*   Updated: 2021/12/09 11:27:24 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 
# endif

# include <stdlib.h>
# include <unistd.h>

typedef enum s_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef struct s_gnl
{
	char		buf[BUFFER_SIZE + 1];
	size_t		index;
	size_t		start;
}	t_gnl;

typedef struct s_gnlist
{
	char			content[BUFFER_SIZE + 1];
	struct s_gnlist	*next;
}		t_gnlist;

void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_gnlstnew(t_gnlist **alst, void *s, size_t start, size_t end);
void		ft_gnlstclear(t_gnlist **alst, void (*del)(void *));
char		*get_next_line(int fd);

#endif
