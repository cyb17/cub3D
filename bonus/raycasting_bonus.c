/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:57:13 by yachen            #+#    #+#             */
/*   Updated: 2024/02/23 17:49:25 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	update_side(t_ray *r, t_player * ply)
{
	if (r->ray_x < 0)
	{
		r->step_x = -1;
		r->side_x = (ply->pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - ply->pos_x) * r->delta_x;
	}
	if (r->ray_y < 0)
	{
		r->step_y = -1;
		r->side_y = (ply->pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - ply->pos_y) * r->delta_y;
	}
}

void	find_ray(t_ray *r, t_player *ply, int x)
{
	r->map_x = (int)ply->pos_x;
	r->map_y = (int)ply->pos_y;
	ply->camera_x = 2 * x / (double)SCREEN_W - 1;
	r->ray_x = ply->dir_x + ply->plane_x * ply->camera_x;
	r->ray_y = ply->dir_y + ply->plane_y * ply->camera_x;
	if (r->ray_x == 0)
		r->delta_x = INFINITY;
	else
		r->delta_x = sqrt(1 + (r->ray_y * r->ray_y) / (r->ray_x * r->ray_x));
	if (r->ray_y == 0)
		r->delta_y = INFINITY;
	else
		r->delta_y = sqrt(1 + (r->ray_x * r->ray_x) / (r->ray_y * r->ray_y));
	update_side(r, ply);
}

void	ft_DDA(t_ray *r, char **map)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map[r->map_x][r->map_y] == '1')
			r->hit = 1;
	}
}
