/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:27:58 by yachen            #+#    #+#             */
/*   Updated: 2024/02/14 10:59:06 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	init_side(t_ray *r, t_player * ply)
{
	if (r->ray_x < 0)
      {
        r->step_x = -1;
        r->side_x = (ply->pos_x - r->map_x) * r->delta_x;
      }
      else
      {
        r->step_x = 1;
        r->sideDist_x = (r->map_x + 1.0 - ply->pos_x) * r->delta_x;
      }
      if (r->rayDir_y < 0)
      {
        r->step_y = -1;
        r->sideDist_y = (ply->pos_y - r->map_y) * r->deltaDist_y;
      }
      else
      {
        r->step_y = 1;
        r->sideDist_y = (r->map_y + 1.0 - ply->pos_y) * r->deltaDist_y;
      }
}

void	init_ray(t_ray *r, t_player *ply)
{
	r->map_x = ply->pos_x;
	r->map_y = ply->pos_y;
	r->ray_x = ply->pos_x + ply->plane_x * ply->camera_x;
	r->ray_y = ply->pos_y + ply->plane_y * ply->camera_x;
	if (r->ray_x == 0)
		r->delta_x = INFINITY;
	else
		r->delta_x = sqrt(1 + (r->ray_y * r->ray_y)/(r->ray_x * r->ray_x));
	if (r->ray_y == 0)
		r->delta_y = INFINITY;
	else
		r->delta_y = sqrt(1 + (r->ray_x * r->ray_x)/(r->ray_y * r->ray_y));
	init_side(r, ply);
	r->p_w_dist;
	r->hit = 0;
	r->side = 0;
}

void	ft_DDA(t_ray *r, char **map)
{
	while (r->hit == 0)
  	{
  	  if (r->side_x < r->sidex_y)
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
  	  if (map[r->map_x][r->map_y] > 0) r->hit = 1;
  	}
}

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
