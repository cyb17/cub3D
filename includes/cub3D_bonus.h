/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:28:54 by yachen            #+#    #+#             */
/*   Updated: 2024/02/27 18:28:49 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define SCREEN_W 1280
# define SCREEN_H 960
# define ROT_SPEED 0.045
# define MOV_SPEED 0.25

// bpp = bit_by_pixels
// ll = line_length
// ed = endian => indique l'ordre d'interpretation des octets

typedef struct s_imge
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
	double	mov_x;
	double	mov_y;		
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
	int		pix_x;
	int		pix_y;
	int		color;
	double	wall_x;
	int		txt_x;
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
	int			minimap;
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
void	update_side(t_ray *r, t_player *ply);
void	find_ray(t_ray *r, t_player *ply, int x);
void	ft_DDA(t_ray *r, char **map);

// update_gameconfig
char	*ft_strim_path(char *path);
void	find_start_position(t_gameconfig *config);
void	init_dir_plane(t_gameconfig *config);
void	get_c_or_f_info(char *str, int tab[3]);
void	update_gameconfig(t_gameconfig *config);

// game_loop
void	put_floor_and_ceiling_to_window(int c[3], int f[3], t_imge *img);
void	loop_ray(t_gameconfig *config);
void	game_loop(t_gameconfig *config, t_imge *img);

// load_imge
t_imge	*load_img(void *mlx, char *path);
int		load_all_texture(t_gameconfig *config, t_draw *d);

// garbage_collector
void	destroye_img(t_gameconfig *config, t_draw *d);
void	clear_list_ptr(t_list **list);
void	garbage_collector(t_gameconfig *src);

// keys_mouse_hook
int		mouse_hook(void *param);
int		key_hook(int keysym, t_gameconfig *config);
void	display(t_gameconfig *config, t_imge *img);

// tools
void	get_ply_wall_dist(t_ray *r, t_player *p);
void	get_draw_info(t_draw *d, t_ray *r);
void	my_mlx_pixel_put(t_imge *img, int x, int y, int color);
int		find_color(int r, int g, int b);
void	put_wall_to_window(t_gameconfig *c, t_imge *img, int x);
void	print_all_data(t_gameconfig *config);

// tools_2
void	find_wall_x(t_gameconfig *c, t_imge *txt);
t_imge	*find_txt_side(t_gameconfig *c);
int		find_txt_pixel_color(t_imge *txt, int x, int y);

// BONUS
void	update_movex_or_movey(t_player *p);
void	create_minicard(t_player *p, char **map, t_imge *img);

#endif