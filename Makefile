# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 10:29:21 by yachen            #+#    #+#              #
#    Updated: 2025/01/10 10:23:50 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

BONUS_NAME = cub3D_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lm -g3

LMX = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux

LIBFTDIR = ./libft

RM = rm -rf

PARSING = check_gamefile is_element is_surrounded_by_wall check_map parsing_tools \

EXECUTION = main garbage_collector init_gameconfig update_gameconfig raycasting \
			load_imge tools keys_mouse_hook game_loop tools_2
			
PARSING_BONUS = check_gamefile_bonus is_element_bonus is_surrounded_by_wall_bonus \
				check_map_bonus parsing_tools_bonus

BONUS = main_bonus garbage_collector_bonus init_gameconfig_bonus update_gameconfig_bonus \
		raycasting_bonus load_imge_bonus tools_bonus keys_mouse_hook_bonus game_loop_bonus \
		minimap_bonus tools_2_bonus rotation_movements
		
SRC = $(addsuffix .c, $(addprefix mandatory/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix mandatory/, $(EXECUTION))) 

BONUS_SRC = $(addsuffix .c, $(addprefix bonus/parsing/, $(PARSING_BONUS))) \
	  		$(addsuffix .c, $(addprefix bonus/, $(BONUS))) 
			
OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
		@echo "\e[32m\n==================================="
		@make -C $(LIBFTDIR) bonus
		@make -C ./mlx_linux
		@echo "\e[32mCompiling cub3D-----------------"
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFTDIR)/libft.a $(LMX) -lXext -lX11 -lm -lz -o $(NAME)
		@echo "\e[32m----created with success : cub3D"
		@echo "\e[32m===================================\n\e[0m"

$(BONUS_NAME): $(BONUS_OBJ)
		@echo "\e[32m\n==================================="
		@make -C $(LIBFTDIR) bonus
		@make -C ./mlx_linux
		@echo "\e[32mCompiling cub3D with BONUS ---------"
		@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFTDIR)/libft.a $(LMX) -lXext -lX11 -lm -lz -o $(BONUS_NAME)
		@echo "\e[32m----created with success : cub3D_bonus"
		@echo "\e[32m===================================\n\e[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@echo "\e[32m\n====================="
	@echo "\e[32mCleaning cub3D----"
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "\e[32m------cub3D Cleaned"
	@make clean -C ./mlx_linux
	@make clean -C $(LIBFTDIR)
	@echo "\e[32m=====================\n\e[0m"

fclean: 
	@echo "\e[32m\n====================="
	@echo "\e[32mCleaning cub3D----"
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@$(RM) $(NAME) $(BONUS_NAME)
	@make clean -C ./mlx_linux
	@make fclean -C $(LIBFTDIR)
	@echo "\e[32m------cub3D Cleaned"
	@echo "\e[32m=====================\n\e[0m"

re: fclean all

.PHONY: clean fclean all re bonus