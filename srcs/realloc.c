/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:37:13 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/27 14:13:38 by qduperon         ###   ########.fr       */
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

	if (size < 1)
		return (NULL);
	if (!ptr)
		return (ft_malloc(size));
	if (!(alloc = search_alloc(ptr)))
		return (NULL);
	diff = size - alloc->size;
	if (diff == 0)
		return (ptr);
	else if (diff < 0 && -diff >= sizeof(t_alloc))
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
