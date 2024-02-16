/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:36:15 by yachen            #+#    #+#             */
/*   Updated: 2024/02/16 10:58:29 by yachen           ###   ########.fr       */
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
	printf("ds: %d de: %d\n", d->draw_start, d->draw_end);
	while (d->draw_start <= d->draw_end)
	{
		my_mlx_pixel_put(img, x, d->draw_start, 200);
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

void	loop_ray(t_gameconfig *config)
{
	int	x;

	x = 0;
	while (x <= SCREEN_W)
	{
		find_ray(&config->ray, &config->player);
		ft_DDA(&config->ray, config->map);
		get_ply_wall_dist(&config->ray);
		get_draw_info(&config->draw, &config->ray);
		put_wall_to_window(&config->draw, &config->img, x);
		x++;
	}
}