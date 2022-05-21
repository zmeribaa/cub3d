# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 15:07:54 by zmeribaa          #+#    #+#              #
#    Updated: 2022/05/21 13:32:28 by zmeribaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
SRC = ./Sources/*.c tools/*.c
O = *.o

MLX = -lmlx -framework OpenGL -framework AppKit

FLAGS = -Wall -Wextra -Werror -O3
DEP = ./Includes/cub3d.h tools/*.h $(SRC)

SANITIZER = -g -fsanitize=address

all: $(NAME)

$(NAME): $(DEP)
		gcc $(SRC) $(FLAGS) $(MLX) $(SANITIZER) -o $(NAME)
clean:
		/bin/rm -f $(O)
fclean: clean
		/bin/rm -f $(NAME)
re: fclean all
