/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:38:30 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/27 14:17:21 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc	*create_alloc(void *addr, size_t size)
{
	t_alloc	*new;

	new = addr;
	new->size = size - sizeof(t_alloc);
	new->status = AVAILABLE;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

t_map	*create_map(size_t map_size, int type)
{
	t_map	*new;
	t_map	*map;

	if ((new = mmap(NULL, map_size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	map = g_map;
	new->type = type;
	new->size = map_size - sizeof(t_map);
	new->next = NULL;
	new->previous = NULL;
	new->alloc = create_alloc((void*)new + sizeof(t_map), new->size);
	if (g_map == NULL)
		g_map = new;
	else
	{
		while (map->next)
			map = map->next;
		map->next = new;
		new->previous = map;
	}
	return (new);
}

void	*new_map(size_t size)
{
	int		type;
	size_t	map_size;
	t_map	*map;
	t_alloc	*alloc;

	type = get_type(size);
	map_size = get_map_size(size, type);
	if ((map = create_map(map_size, type)) == NULL)
		return (NULL);
	if ((alloc = get_alloc(map->alloc, size + sizeof(t_alloc))) == NULL)
		return (NULL);
	alloc->status = USED;
	return ((void *)alloc + sizeof(t_alloc));
}
