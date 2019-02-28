# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/16 13:22:36 by qduperon          #+#    #+#              #
#    Updated: 2019/02/28 18:38:42 by qduperon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                               // NAME \\                                     #
#==============================================================================#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LINK = libft_malloc.so


#==============================================================================#
#                           //  VARIABLES  \\                                  #
#==============================================================================#

LIBFTDIR = libft/

LIBFT = libft/libft.a

INCSDIR = includes/

SRCSDIR = srcs/

OBJSDIR = objs/

CC = gcc

FLAGS = -Wpadded -Wall -Werror -Wextra

SRCS =	calloc.c \
		free.c \
		get.c \
		init.c \
		malloc.c \
		realloc.c \
		reallocf.c \
		search.c \
		show.c

#==============================================================================#
#                             // OBJECTS \\                                    #
#==============================================================================#

OBJS = $(addprefix $(OBJSDIR),$(SRCS:.c=.o))

#==============================================================================#
#                            // COMPILATION \\                                 #
#==============================================================================#

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	mkdir -p $(OBJSDIR)
	$(CC) $(FLAGS) -fPIC -I $(INCSDIR) -I libft/includes -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(FLAGS) -shared -o $(NAME) $(OBJS) -L./libft -lft
	ln -sf $(NAME) $(LINK)

#==============================================================================#
#                              // DELETING \\                                  #
#==============================================================================#

clean:
	make clean -C libft
	rm -rf $(OBJSDIR)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(LINK)

#==============================================================================#
#                             // RETRY \\                                      #
#==============================================================================#

re: fclean all

.PHONY : all clean fclean re
