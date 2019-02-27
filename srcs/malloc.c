/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:37:24 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/27 14:17:54 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_malloc(size_t size)
{
	void *addr;

	if (size < 1)
		return (NULL);
	if ((addr = get_from_gmap(size)) != NULL)
		return (addr);
	if ((addr = new_map(size)) != NULL)
		return (addr);
	return (NULL);
}
