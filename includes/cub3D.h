/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:28:54 by yachen            #+#    #+#             */
/*   Updated: 2024/02/08 14:41:56 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define SCREEN_W 640
# define SCREEN_H 480
// # define TILE_SIZE 30
# define FOV 0.66

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	camera_x;
	float	camera_y;
}			t_player;

typedef struct s_gameconfig
{
	t_list		*file;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	int			nb_element;
	char		**map;
	t_player	*player;
	void		*mlx;
	void		*mlx_w;

}				t_gameconfig;

/* PARSING */

// check_gamefile
int		check_file_path(char *gamefile);
void	read_file_to_list(int fd, t_gameconfig *config);
int		make_map(t_list *start, t_gameconfig *config);
int		get_info_from_list(t_gameconfig *config);
int		check_gamefile(char *gamefile, t_gameconfig *config);

// check_map
int		check_wall(char **map, int size);
int		check_map_content(char **map, int size);

// is_element
int		element_already_present(char *line, t_gameconfig *config);
int		with_correct_info(char *line);
int		is_element(char *line);

// is_surrounded_by_wall
int		is_surrounded_by_walls(char **map, int size, int i, int j);

int		parsing(char *gamefile, t_gameconfig *config);
void	clear_list_ptr(t_list **list);
void	garbage_collector(t_gameconfig *src);

// parsing_tools
int		err(char *msg1, char *msg2, char *msg3);
int		find_size(t_list *start);
int		is_start_map(char *line);
int		is_empty_line(char *line);
char	*delete_white_space(char *line);


/* EXECUTION */

// game_initialization
void	init_config(t_gameconfig *config);



#endif