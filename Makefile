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

NAME =			fractol
HEADER =		-I ./includes \
				-I ./libft/includes
CFLAGS =		-Werror #-Wall -Wextra
LIBS =			-lft -L ./libft \
				-lmlx
FRAMEWORKS =	-framework OpenGL \
				-framework AppKit \
				-framework OpenCL
LIST =			draw \
				init \
				key_hook \
				main 
OBJ = $(addprefix obj/, $(addsuffix .o, $(LIST)))

all: $(NAME)

obj/%.o: src/%.c
	@gcc $(CFLAGS) -c $< -o $@ $(HEADER)

$(NAME): obj $(OBJ)
	@make -C libft
	@gcc $(OBJ) -o $(NAME) $(LIBS) $(FRAMEWORKS)

obj:
	@mkdir obj

clean:
	@make -C libft clean
	@rm -rf obj
	
fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all
