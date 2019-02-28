/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:37:13 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/28 18:46:06 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*make_re(void *ptr, size_t size, size_t alloc_size)
{
	char	*src;
	char	*dst;
	size_t	i;

	src = (char *)ptr;
	if (!(dst = (char *)ft_malloc(size)))
		return (NULL);
	i = 0;
	while (i < size && i < alloc_size)
	{
		dst[i] = src[i];
		i++;
	}
	ft_free(ptr);
	return ((void *)dst);
}

void	resize(t_alloc *alloc, size_t size, int diff)
{
	t_alloc	*next;
	size_t	next_size;

	next = alloc->next;
	next_size = next->size;
	alloc->next = (void *)alloc->next + diff;
	alloc->next->next = next->next;
	alloc->next->size = next_size - diff;
	alloc->next->status = AVAILABLE;
	alloc->next->previous = alloc;
	alloc->size = size;
}

void	*ft_realloc(void *ptr, size_t size)
{
	int		diff;
	t_alloc	*alloc;

	if (!ptr)
		return (ft_malloc(size));
	if ((int)size < 1 || !(alloc = search_alloc(ptr)))
		return (NULL);
	while (size % 16 != 0)
		size++;
	diff = size - alloc->size;
	if (diff == 0)
		return (ptr);
	else if (diff < 0 && -diff >= (int)sizeof(t_alloc))
	{
		get_alloc(alloc, -diff);
		return (ptr);
	}
	else if (alloc->next && diff > 0 && alloc->next->status == AVAILABLE
		&& (int)alloc->next->size >= diff)
	{
		resize(alloc, size, diff);
		return (ptr);
	}
	else
		return (make_re(ptr, size, alloc->size));
}

void	*realloc(void *ptr, size_t size)
{
	void	*ret;

	if (g_lock == 0)
	{
		g_lock = 1;
		ret = ft_realloc(ptr, size);
		g_lock = 0;
		return (ret);
	}
	else
		return (NULL);
}
