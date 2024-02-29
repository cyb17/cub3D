/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:34:01 by yachen            #+#    #+#             */
/*   Updated: 2024/02/29 14:30:25 by yachen           ###   ########.fr       */
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
