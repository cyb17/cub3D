# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 10:29:21 by yachen            #+#    #+#              #
#    Updated: 2024/02/19 16:24:54 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lm -g3

LMX = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux

LIBFTDIR = ./libft

RM = rm -rf

PARSING = check_gamefile is_element is_surrounded_by_wall check_map parsing_tools \

EXECUTION = main garbage_collector init_gameconfig update_gameconfig raycasting \
			load_imge tools keys_mouse_hook game_loop

SRC = $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/, $(EXECUTION))) \
	  
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@echo "\e[32m\n==================================="
		@make -C $(LIBFTDIR) bonus
		@make -C ./mlx_linux
		@echo "\e[32mCompiling cub3D-----------------"
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFTDIR)/libft.a $(LMX) -lXext -lX11 -lm -lz -o $(NAME)
		@echo "\e[32m----created with success : cub3D"
		@echo "\e[32m===================================\n\e[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@echo "\e[32m\n====================="
	@echo "\e[32mCleaning cub3D----"
	@$(RM) $(OBJ)
	@echo "\e[32m------cub3D Cleaned"
	@make clean -C ./mlx_linux
	@make clean -C $(LIBFTDIR)
	@echo "\e[32m=====================\n\e[0m"

fclean: 
	@echo "\e[32m\n====================="
	@echo "\e[32mCleaning cub3D----"
	@$(RM) $(OBJ)
	@$(RM) $(NAME)
	@make clean -C ./mlx_linux
	@make fclean -C $(LIBFTDIR)
	@echo "\e[32m------cub3D Cleaned"
	@echo "\e[32m=====================\n\e[0m"

re: fclean all

.PHONY: clean fclean all re