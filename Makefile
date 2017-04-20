# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chansen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/20 04:20:00 by chansen           #+#    #+#              #
#    Updated: 2017/04/20 04:20:00 by chansen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = src/*.c \

LFT = -I libft -L libft -lft

MLX = -I minilibx -L minilibx -lmlx

FRAME = -framework OpenGL -framework Appkit

RM = rm -rf

all: $(NAME)

$(NAME):
	make -C ./libft/ re
	make -C ./minilibx/ re
	$(CC) $(CFLAGS) $(LFT) $(MLX) $(FRAME) $(SRC) -o $(NAME)

clean:
	make -C ./libft/ clean

fclean:
	make -C ./minilibx/ clean
	make -C ./libft/ fclean
	$(RM) $(NAME)

re:
	make fclean
	make all
