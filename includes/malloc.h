/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:37:45 by qduperon          #+#    #+#             */
/*   Updated: 2019/02/28 14:36:44 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY 128
# define SMALL 1024
# define LARGE 9999999

# define USED 0
# define AVAILABLE 1

# define TRUE 1
# define FALSE 0

# include <sys/mman.h>
# include <unistd.h>

# include "libft.h"

typedef struct		s_map
{
	int				type;
	size_t			size;
	struct s_map	*next;
	struct s_map	*previous;
	struct s_alloc	*alloc;
}					t_map;

typedef struct		s_alloc
{
	int				status;
	size_t			size;
	struct s_alloc	*next;
	struct s_alloc	*previous;
}					t_alloc;

t_map				*g_map;

/*
***	free.c
*/
int					check_available(t_map *map);
void				free(void *ptr);
void				merge_alloc(t_alloc *ptr);
void				rm_map(t_map *map);

/*
***	get.c
*/
int					get_type(size_t size);
size_t				get_map_size(size_t size, size_t type);
t_alloc				*get_from_existing_alloc(t_alloc *alloc, size_t size);
t_alloc				*get_alloc(t_alloc *alloc, size_t size);
void				*get_from_gmap(size_t size);

/*
***	init.c
*/
t_alloc				*create_alloc(void *addr, size_t size);
t_map				*create_map(size_t map_size, int type);
void				*new_map(size_t size);

/*
***	malloc.c
*/
void				*malloc(size_t size);

/*
***	realloc.c
*/
void				*make_re(void *ptr, size_t size, size_t alloc_size);
void				*realloc(void *ptr, size_t size);
void				resize(t_alloc *alloc, size_t size, int diff);

/*
***	search.c
*/
t_alloc				*search_alloc(void *ptr);
t_map				*search_map(t_alloc *ptr);

/*
***	show.c
*/
void				print_addr(void *ptr);
void				print_alloc(t_alloc *alloc, size_t *total);
void				print_map(t_map *map);
void				show_alloc_mem(void);

#endif
