/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:28:47 by yachen            #+#    #+#             */
/*   Updated: 2024/02/22 16:10:55 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	loop_ray(t_gameconfig *config)
{
	int	x;

	x = 0;
	while (x < SCREEN_W)
	{
		config->ray.p_w_dist = 0;
		find_ray(&config->ray, &config->player, x);
		ft_DDA(&config->ray, config->map);
		get_ply_wall_dist(&config->ray, &config->player);
		get_draw_info(&config->draw, &config->ray);
		if (x == 0 || x == 320 || x == 639)
		{
			print_all_data(config, x);
			find_pixel_color_in_txt(config, &config->draw, config->draw.txt_no);
		}
		put_wall_to_window(config, &config->ray, &config->draw, &config->img, x);
		x++;
	}
}

void	put_floor_and_ceiling_to_window(int c[3], int f[3], t_imge *img)
{
	int	floor;
	int	ceiling;
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

void	display(t_gameconfig *config, t_imge *img)
{
	put_floor_and_ceiling_to_window(config->draw.c, config->draw.f, img);
	loop_ray(config);
	mlx_put_image_to_window(config->mlx, config->mlx_w, img->img, 0, 0);
}

void	game_loop(t_gameconfig *config, t_imge *img)
{
	config->mlx = mlx_init();
	config->mlx_w = mlx_new_window(config->mlx, SCREEN_W, SCREEN_H, "cub3D");
	img->img = mlx_new_image(config->mlx, SCREEN_W, SCREEN_H);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->ed);
	if (load_all_texture(config, &config->draw) == -1)
	{
		garbage_collector(config);
		exit(1);
	}
	put_floor_and_ceiling_to_window(config->draw.c, config->draw.f, img);
	loop_ray(config);
	mlx_put_image_to_window(config->mlx, config->mlx_w, img->img, 0, 0);
	mlx_hook(config->mlx_w, KeyPress, KeyPressMask, key_hook, config);
	mlx_hook(config->mlx_w, 17, 0, mouse_hook, config);
	mlx_loop(config->mlx);
}
