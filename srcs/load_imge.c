/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_imge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:03 by yachen            #+#    #+#             */
/*   Updated: 2024/02/14 14:04:50 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_ply_wall_dist(t_ray *r)
{
	if(r->side == 0) 
		r->p_w_dist = (r->side_x - r->delta_x);
    else
	  r->p_w_dist = (r->side_y - r->delta_y);
}

void	get_draw_info(t_draw *d, t_ray *r)
{
	d->wall_height = SCREEN_H / r->p_w_dist;
	d->draw_start = SCREEN_H / 2 - wall_height / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = SCREEN_H / 2 + wall_height / 2;
	if (d->draw_end >= SCREEN_H)
		d->draw_end = SCREEN_H - 1;
}

int	load_imge(t_gameconfig *config, t_draw *d)
{
	d->txt_no = load_img(config->mlx, "path");
	d->txt_so = load_img(config->mlx, "path");
	d->txt_we = load_img(config->mlx, "path");
	d->txt_ea = load_img(config->mlx, "path");
	if (!d->txt_no || !d->txt_so || !d->txt_we || !d->txt_ea)
		return (err("Error!\n", "loading image failed", ""));
	return (0);
}
