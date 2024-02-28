/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:34:01 by yachen            #+#    #+#             */
/*   Updated: 2024/02/28 10:50:50 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_ply_wall_dist(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->p_w_dist = ((double)r->map_x - p->pos_x
				+ (1 - (double)r->step_x) / 2) / r->ray_x;
	else
		r->p_w_dist = ((double)r->map_y - p->pos_y
				+ (1 - (double)r->step_y) / 2) / r->ray_y;
}

void	get_draw_info(t_draw *d, t_ray *r)
{
	d->wall_height = (int)(SCREEN_H / r->p_w_dist);
	d->draw_start = SCREEN_H / 2 - d->wall_height / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = SCREEN_H / 2 + d->wall_height / 2;
	if (d->draw_end >= SCREEN_H)
		d->draw_end = SCREEN_H - 1;
}

void	my_mlx_pixel_put(t_imge *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	find_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}



// void    print_all_data(t_gameconfig *config)
// {
//     t_draw        *d = &config->draw;
//     t_ray        *r = &config->ray;
//     t_player    *p = &config->player;
//     printf("wall_height:%d\ndraw_start:%d\ndraw_end:%d\n", d->wall_height, d->draw_start, d->draw_end);
//     printf("---RAY_INFO \nmap_x:%d\n", r->map_x);
//     printf("map_y:%d\ncamera_x:%f\n", r->map_y, p->camera_x);
//     printf("ray_x: %f\n", r->ray_x);
//     printf("ray_y: %f\n", r->ray_y);
//     printf("delta_x: %f\n", r->delta_x);
//     printf("delta_y: %f\n", r->delta_y);
//     printf("side_x: %f\n", r->side_x);
//     printf("side_y: %f\n", r->side_y);
//     printf("p_w_dist: %f\n", r->p_w_dist);
//     printf("step_x: %d\n", r->step_x);
//     printf("step_y: %d\n", r->step_y);
//     printf("hit: %d\n", r->hit);
//     printf("side: %d\n", r->side);
//     printf("---PLAYER_INFO:\n");
//     printf("pos_x: %f\n", p->pos_x);
//     printf("pos_y: %f\n", p->pos_y);
//     printf("dir_x: %f\n", p->dir_x);
//     printf("dir_y: %f\n", p->dir_y);
//     printf("plane_x: %f\n", p->plane_x);
//     printf("plane_y: %f\n", p->plane_y);
//     printf("camera_x: %f\n\n----------------\n", p->camera_x);
// }

// void	put_wall_to_window(t_gameconfig *c, t_imge *img, int x)
// {
// 	t_ray	*r;
// 	t_draw	*d;

// 	r = &c->ray;
// 	d = &c->draw;
// 	while (d->draw_start <= d->draw_end)
// 	{
// 		if (r->side == 1)
// 		{
// 			if (r->ray_y < 0)
// 				my_mlx_pixel_put(img, x, d->draw_start, find_color(255, 255, 255)); // W_wall
// 			else
// 				my_mlx_pixel_put(img, x, d->draw_start, find_color(160, 160, 160)); // E_wall
// 		}
// 		else
// 		{
// 			if (r->ray_x < 0)
// 				my_mlx_pixel_put(img, x, d->draw_start, find_color(0, 0, 0)); // N_wall
// 			else
// 				my_mlx_pixel_put(img, x, d->draw_start, find_color(96, 96, 96)); // S_wall
// 		}
// 		d->draw_start++;
// 	}
// }
