# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 01:37:39 by ztouzri           #+#    #+#              #
#    Updated: 2021/10/11 14:08:16 by ztouzri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
NAME	= cub3D
LIB		= libft.a
SRCS	= main.c parsing.c checker.c fill.c fill1.c free.c print.c
OBJS	= $(SRCS:c=o)

.c.o:
	$(CC) $(CFLAGS) $< -c -I./libft

$(NAME):	$(OBJS)
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