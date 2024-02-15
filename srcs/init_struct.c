/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:47 by yachen            #+#    #+#             */
/*   Updated: 2024/02/15 13:31:31 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	init_imge(t_imge *imge)
{
	imge->img = NULL;
	imge->addr = NULL;
	imge->width = 0;
	imge->height = 0;
	imge->bpp = 0;
	imge->ll = 0;
	imge->ed = 0;
}

static void	init_draw(t_draw *draw)
{
	draw->wall_height = 0;
	draw->draw_start = 0;
	draw->draw_end = 0;
	draw->txt_no = NULL;
	draw->txt_so = NULL;
	draw->txt_we = NULL;
	draw->txt_ea = NULL;
	ft_memset(draw->c,0, 3);
	ft_memset(draw->f,0, 3);
}

static void	init_ray(t_ray *r)
{
	r->map_x = 0;
	r->map_y= 0;
	r->ray_x = 0.0;
	r->ray_y = 0.0;
	r->delta_x = 0.0;
	r->delta_y = 0.0;
	r->side_x = 0;
	r->side_y = 0;
	r->p_w_dist = 0;
	r->step_x = 0;
	r->step_y = 0;
	r->hit = 0;
	r->side = 0;
}

void	init_gameconfig(t_gameconfig *config)
{
	config->file = NULL;
	config->map = NULL;
	config->mlx = NULL;
	config->mlx_w = NULL;
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->f = NULL;
	config->c = NULL;
	config->nb_element = 0;
	config->player.pos_x = 0.0;
	config->player.pos_y = 0.0;
	config->player.dir_x = -1;
	config->player.dir_y = 0;
	config->player.plane_x = 0;
	config->player.plane_y = 0;
	config->player.camera_x = 0;
	init_ray(&config->ray);
	init_draw(&config->draw);
	init_imge(&config->img);
}
