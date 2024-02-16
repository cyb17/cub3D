/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:28:54 by yachen            #+#    #+#             */
/*   Updated: 2024/02/16 09:48:50 by jp-de-to         ###   ########.fr       */
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

// bpp = bit_by_pixels
// ll = line_length
// ed = endian => indique l'ordre d'interpretation des octets
typedef struct	s_imge
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		ll;
	int		ed;
}				t_imge;

typedef struct s_player
{
	char	start_pos;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
}			t_player;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	ray_x;
	double	ray_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	p_w_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}			t_ray;

typedef struct s_draw
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	t_imge	*txt_no;
	t_imge	*txt_so;
	t_imge	*txt_we;
	t_imge	*txt_ea;
	int		c[3];
	int		f[3];
}		t_draw;

typedef struct s_gameconfig
{
	t_list		*file;
	char		**map;
	void		*mlx;
	void		*mlx_w;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	int			nb_element;
	t_player	player;
	t_ray		ray;
	t_draw		draw;
	t_imge		img;


}				t_gameconfig;

/* PARSING */

// check_gamefile
int		check_file_path(char *gamefile);
void	read_file_to_list(int fd, t_gameconfig *config);
int		make_map(t_list *start, char ***map);
int		get_info_from_list(t_gameconfig *config);
int		check_gamefile(char *gamefile, t_gameconfig *config);

// check_map
int		check_wall(char **map, int size);
int		check_map_content(char **map, int size);
int		check_gameconfig_content(t_gameconfig *config);

// is_element
int		element_already_present(char *line, t_gameconfig *config);
int		with_correct_info(char *line);
int		is_element(char *line);
char	*ft_strim_path(char *path);

// is_surrounded_by_wall
int		is_surrounded_by_walls(char **map, int size, int i, int j);

// parsing_tools
int		err(char *msg1, char *msg2, char *msg3);
int		find_size(t_list *start);
int		is_start_map(char *line);
int		is_empty_line(char *line);
char	*delete_white_space(char *line);


/* EXECUTION */

// init_struct
void	init_gameconfig(t_gameconfig *config);

// raycasting
void	find_ray(t_ray *r, t_player *ply);
void	ft_DDA(t_ray *r, char **map);

// game_update
void	update_gameconfig(t_gameconfig *config);

// player
char	*ft_strim_path(char *path);
void	find_start_position(t_gameconfig *config);
void	if_start_pos_found(t_gameconfig *config);

// load_imge
t_imge	*load_img(void *mlx, char *path);
int		load_all_texture(t_gameconfig *config, t_draw *d);
// void	get_c_code(char *c, t_draw *d);
// void	get_f_code(char *f, t_draw *d);
void	get_c_or_f_info(char *str, int tab[3]);

// garbage_collector
void	destroye_img(t_gameconfig *config, t_draw *d);
void	clear_list_ptr(t_list **list);
void	garbage_collector(t_gameconfig *src);

// tools
void	get_ply_wall_dist(t_ray *r);
void	get_draw_info(t_draw *d, t_ray *r);
void	my_mlx_pixel_put(t_imge *img, int x, int y, int color);
int		find_color(int r, int g, int b);

// display
void	put_floor_and_ceiling_to_window(int c[3], int f[3], t_imge *img);

// keys
int	shut_down_game(void *param);

#endif