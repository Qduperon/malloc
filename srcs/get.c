/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:42:23 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/27 14:10:34 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		get_type(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else if (size <= SMALL)
		return (SMALL);
	else
		return (LARGE);
}

t_alloc	*get_alloc(t_alloc *alloc, size_t size)
{
	t_alloc	*new;

	if (alloc->size == size - sizeof(t_alloc))
		return (alloc);
	else if (alloc->size < size)
		return (NULL);
	new = (t_alloc*)((void*)alloc + alloc->size + sizeof(t_alloc) - size);
	alloc->size -= size;
	new->size = size - sizeof(t_alloc);
	new->status = AVAILABLE;
	new->next = alloc->next;
	new->previous = alloc;
	alloc->next = new;
	if (new->next)
		new->next->previous = new;
	return (new);
}

t_alloc	*get_from_existing_alloc(t_alloc *alloc, size_t size)
{
	while (alloc && alloc->previous)
		alloc = alloc->previous;
	while (alloc)
	{
		if (alloc->size >= size + sizeof(t_alloc) && alloc->status == AVAILABLE)
			return (get_alloc(alloc, size + sizeof(t_alloc)));
		alloc = alloc->next;
	}
	return (NULL);
}

void	*get_from_gmap(size_t size)
{
	int		type;
	t_map	*map;
	t_alloc	*alloc;

	type = get_type(size);
	map = g_map;
	alloc = NULL;
	while (map)
	{
		if (map->type == type)
		{
			alloc = get_from_existing_alloc(map->alloc, size);
			if (alloc)
			{
				alloc->status = USED;
				return ((void*)alloc + sizeof(t_alloc));
			}
		}
		map = map->next;
	}
	return (NULL);
}

size_t	get_map_size(size_t size, size_t type)
{
	size_t	i;

	i = 1;
	if (type == TINY)
		while (i * getpagesize() < ((TINY + sizeof(t_alloc)) * 100)
				+ sizeof(t_map))
			i++;
	else if (type == SMALL)
		while (i * getpagesize() < ((SMALL + sizeof(t_alloc)) * 100)
				+ sizeof(t_map))
			i++;
	else
		while (i * getpagesize() < ((size + sizeof(t_alloc)) * 1)
				+ sizeof(t_map))
			i++;
	return (getpagesize() * i);
}
