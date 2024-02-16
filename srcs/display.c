/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:36:15 by yachen            #+#    #+#             */
/*   Updated: 2024/02/16 15:27:32 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_floor_and_ceiling_to_window(int c[3], int f[3], t_imge *img)
{
	int	floor;
	int ceiling;
	int	x;
	int	y;

	floor = find_color(f[0], f[1], f[2]);
	ceiling = find_color(c[0], c[1], c[2]);
	y = 0;
	while (y <= SCREEN_H)
	{
		x = 0;
		while (x <= SCREEN_W)
		{
			if (y < SCREEN_H / 2)
				my_mlx_pixel_put(img, x, y, ceiling);
			else
				my_mlx_pixel_put(img, x, y, floor);
			x++;
		}
		y++;
	}
}

void	put_wall_to_window(t_draw *d, t_imge *img, int x)
{
	while (d->draw_start <= d->draw_end)
	{
		my_mlx_pixel_put(img, x, d->draw_start, 16216947);
		d->draw_start++;
	}
}

void	update_gameconfig(t_gameconfig *config)
{
	find_start_position(config);
	if_start_pos_found(config);
	// find_ray(&config->ray, &config->player);
	// ft_DDA(&config->ray, config->map);
	// get_ply_wall_dist(&config->ray);
	// get_draw_info(&config->draw, &config->ray);
	get_c_or_f_info(config->c, config->draw.c);
	get_c_or_f_info(config->f, config->draw.f);
}

void    print_all_data(t_gameconfig *config)
{
    t_draw        *d = &config->draw;
    t_ray        *r = &config->ray;
    t_player    *p = &config->player;
    printf("wall_height:%d\ndraw_start:%d\ndraw_end:%d\n", d->wall_height, d->draw_start, d->draw_end);
    printf("---RAY_INFO \nmap_x:%d\n", r->map_x);
    printf("map_y:%d\ncamera_x:%f\n", r->map_y, p->camera_x);
    printf("ray_x: %f\n", r->ray_x);
    printf("ray_y: %f\n", r->ray_y);
    printf("delta_x: %f\n", r->delta_x);
    printf("delta_y: %f\n", r->delta_y);
    printf("side_x: %f\n", r->side_x);
    printf("side_y: %f\n", r->side_y);
    printf("p_w_dist: %f\n", r->p_w_dist);
    printf("step_x: %d\n", r->step_x);
    printf("step_y: %d\n", r->step_y);
    printf("hit: %d\n", r->hit);
    printf("side: %d\n", r->side);
    printf("---PLAYER_INFO:\n");
    printf("pos_x: %f\n", p->pos_x);
    printf("pos_y: %f\n", p->pos_y);
    printf("dir_x: %f\n", p->dir_x);
    printf("dir_y: %f\n", p->dir_y);
    printf("plane_x: %f\n", p->plane_x);
    printf("plane_y: %f\n", p->plane_y);
    printf("camera_x: %f\n\n----------------\n", p->camera_x);

}

void	loop_ray(t_gameconfig *config)
{
	int	x;

	x = 0;
	while (x <= SCREEN_W)
	{
		config->ray.hit = 0;
		find_ray(&config->ray, &config->player, x);
		ft_DDA(&config->ray, config->map);
		get_ply_wall_dist(&config->ray, &config->player);
		get_draw_info(&config->draw, &config->ray);
		if (x == 0 || x == 320 || x == 640)
			print_all_data(config);
		put_wall_to_window(&config->draw, &config->img, x);
		x++;
	}
}
