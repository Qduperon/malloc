/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:26:46 by qduperon          #+#    #+#             */
/*   Updated: 2019/03/11 11:02:54 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	x;

	if ((int)count < 1)
		count = 1;
	if ((int)size < 1)
		size = 1;
	x = count * size;
	while (x % 16 != 0)
		x++;
	if ((ptr = malloc(x)))
		ft_bzero(ptr, x);
	return (ptr);
}
