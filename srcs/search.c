/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:44:41 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/27 14:14:36 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map	*search_map(t_alloc *ptr)
{
	t_map	*map;
	t_alloc	*alloc;

	map = g_map;
	while (map)
	{
		alloc = map->alloc;
		while (alloc)
		{
			if (alloc == ptr)
				return (map);
			alloc = alloc->next;
		}
		map = map->next;
	}
	return (NULL);
}

t_alloc	*search_alloc(void *ptr)
{
	t_map	*map;
	t_alloc	*alloc;

	map = g_map;
	alloc = NULL;
	while (map)
	{
		alloc = map->alloc;
		while (alloc)
		{
			if ((void*)alloc + sizeof(t_alloc) == ptr)
				return (alloc);
			alloc = alloc->next;
		}
		map = map->next;
	}
	return (NULL);
}
