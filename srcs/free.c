/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:37:32 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/28 18:29:21 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		check_available(t_map *map)
{
	t_alloc *alloc;

	alloc = map->alloc;
	while (alloc)
	{
		if (alloc->status == USED)
			return (FALSE);
		alloc = alloc->next;
	}
	return (TRUE);
}

void	rm_map(t_map *map)
{
	t_map *prev;
	t_map *next;

	next = map->next;
	prev = map->previous;
	if (next)
		next->previous = prev;
	if (prev)
		prev->next = next;
	if (map == g_map)
		g_map = next;
	munmap((void *)map, map->size + sizeof(t_map));
}

void	merge_alloc(t_alloc *ptr)
{
	t_alloc *prev;
	t_alloc *next;

	ptr->status = AVAILABLE;
	next = ptr->next;
	prev = ptr->previous;
	if (next && next->status == AVAILABLE)
	{
		ptr->size += next->size + sizeof(t_alloc);
		ptr->next = next->next;
	}
	if (prev && prev->status == AVAILABLE)
	{
		prev->size += ptr->size + sizeof(t_alloc);
		prev->next = ptr->next;
	}
}

void	ft_free(void *ptr)
{
	t_alloc *alloc;
	t_map	*map;

	if (ptr == NULL)
		return ;
	if ((alloc = search_alloc(ptr)) == NULL)
		return ;
	if ((map = search_map(alloc)) == NULL)
		return ;
	merge_alloc(alloc);
	if (map->type == LARGE && check_available(map) == TRUE)
		rm_map(map);
}

void	free(void *ptr)
{
	if (g_lock == 0)
	{
		g_lock = 1;
		ft_free(ptr);
		g_lock = 0;
	}
}
