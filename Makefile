# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 01:37:39 by ztouzri           #+#    #+#              #
#    Updated: 2021/10/24 15:38:09 by ztouzri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
NAME	= cub3D
LIB		= libft.a
SRCS	= main.c parsing.c checker.c fill.c fill1.c free.c print.c events.c
OBJS	= $(SRCS:c=o)
INCS	= cub3d.h

.c.o:
	$(CC) $(CFLAGS) $< -c -I./libft

$(NAME):	$(OBJS) $(INCS)
	make -C libft/
	mv libft/$(LIB) .
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

.PHONY: all clean fclean re bonus

all: $(NAME)

clean:
	$(RM) $(OBJS) $(LIB)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

bonus: