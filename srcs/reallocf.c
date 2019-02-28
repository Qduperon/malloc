/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:35:47 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/28 18:35:58 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_reallocf(void *ptr, size_t size)
{
	void *ret;

	if (!(ret = ft_realloc(ptr, size)))
	{
		ft_free(ptr);
		return (NULL);
	}
	return (ret);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*ret;

	if (g_lock == 0)
	{
		g_lock = 1;
		ret = ft_reallocf(ptr, size);
		g_lock = 0;
		return (ret);
	}
	else
		return (NULL);
}
