# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osamoile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/01 15:53:40 by osamoile          #+#    #+#              #
#    Updated: 2018/08/01 15:53:44 by osamoile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
HEADER = -I ./includes -I ./libft/includes 
# FLAGS = -Wall -Werror -Wextra
LIBFLAGS = libft/libft.a -lmlx -framework OpenGL -framework AppKit
OBJ_DIR = obj
SRC_DIR = src

LIST =	draw \
		init \
		key_hook \
		main

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(LIST)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(LIST)))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc $(FLAGS) -o $@ -c $< $(HEADER)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(FLAGS) $(LIBFLAGS) $(OBJ) -o $(NAME) $(HEADER)

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all
