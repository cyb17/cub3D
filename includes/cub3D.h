/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:28:54 by yachen            #+#    #+#             */
/*   Updated: 2024/01/19 17:10:33 by yachen           ###   ########.fr       */
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

# define FOV 
# define DISTANCE_SCREEN_PLAYER
# define GAZE_HEIGHT 
# define RESOLUTION

typedef struct s_element
{
	char	id;
	char	*info;
	void	*img;
	int		weidth;
	int		height;
}			t_element;

// typedef struct s_map
// {
	// char	**mapptr;
	// void	*mlx;
	// void	*mlx_w;
	// float	x_ply;
	// float	y_ply;
	//direction du regard
	// float	x_wall;
	// float	y_wall;
// }			t_map;					

typedef struct s_gameconfig
{
	t_list		*file;
	t_element	*no;
	t_element	*so;
	t_element	*we;
	t_element	*ea;
	t_element	*f;
	t_element	*c;
	int			nb_element;
	char		**map;
	void		*mlx;
	void		*mlx_w;

}				t_gameconfig;

int		parsing(char *gamefile, t_gameconfig *config);
void	clear_list_ptr(t_list **list);
void	garbage_collector(t_gameconfig *src);

#endif