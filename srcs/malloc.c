/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:37:24 by qduperon          #+#    #+#             */
/*   Updated: 2019/03/11 11:04:37 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void *addr;

	if ((int)size < 1)
		return (NULL);
	while (size % 16 != 0)
		size++;
	if ((addr = get_from_gmap(size)) != NULL)
		return (addr);
	if ((addr = new_map(size)) != NULL)
		return (addr);
	return (NULL);
}
