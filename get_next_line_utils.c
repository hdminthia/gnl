/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:17:14 by hdo-minh          #+#    #+#             */
/*   Updated: 2021/12/09 11:20:05 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static long	ft_set_bit(int c)
{
	long	wc_value;

	wc_value = (long)c & 0xff;
	wc_value |= wc_value << 8;
	wc_value |= wc_value << 16;
	wc_value |= (wc_value << 16) << 16;
	return (wc_value);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr_c;
	unsigned char	c_value;
	long			*ptr_wc;
	long			wc_value;
	size_t			data;

	c_value = (unsigned char)c & 0xff;
	wc_value = ft_set_bit(c);
	ptr_c = (unsigned char *)s;
	ptr_wc = (long *)ptr_c;
	data = n >> 3;
	n &= 7;
	while (data--)
		*ptr_wc++ = wc_value;
	ptr_c = (unsigned char *)ptr_wc;
	while (n--)
		*ptr_c++ = c_value;
	return (s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	long			*ptr_dst;
	long			*ptr_src;
	unsigned char	*src_value;
	unsigned char	*dst_value;
	size_t			data;

	if ((!dest && !src) || !n)
		return (dest);
	ptr_dst = (long *)dest;
	ptr_src = (long *)src;
	data = n >> 3;
	n &= 7;
	while (data--)
		*ptr_dst++ = *ptr_src++;
	dst_value = (unsigned char *)ptr_dst;
	src_value = (unsigned char *)ptr_src;
	while (n--)
		*dst_value++ = *src_value++;
	*dst_value = '\0';
	return (dest);
}

void	ft_gnlstnew(t_gnlist **alst, void *s, size_t start, size_t end)
{
	t_gnlist	*current;	
	t_gnlist	*new;
	char		*str;

	if (!alst)
		return ;
	str = (char *)s;
	new = malloc(sizeof(t_gnlist));
	if (!new)
		return ;
	ft_memcpy(new->content, &str[start], end - start + 1);
	new->next = NULL;
	if (!*alst)
		*alst = new;
	else
	{
		current = *alst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	ft_gnlstclear(t_gnlist **alst, void (*del)(void *))
{
	t_gnlist	*tmp;

	if (!del || !alst || !(*alst))
		return ;
	tmp = *alst;
	while (*alst)
	{
		tmp = (*alst)->next;
		free(*alst);
		*alst = tmp;
	}
}
