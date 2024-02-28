/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:28:47 by yachen            #+#    #+#             */
/*   Updated: 2024/02/28 15:19:41 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	put_pixel_col(t_gameconfig *c, t_imge *txt, int x)
{
	double	scale;
	int		*column;
	int		i;
	int		j;

	column = (int *)malloc(sizeof(int) * c->draw.wall_height);
	if (!column)
		return (err("Error!\n", "Malloc failed: put_pixel_col\n", ""));
	scale = 1.0 * txt->height / c->draw.wall_height;
	i = -1;
	int tmp = 0;
	if (c->draw.wall_height > SCREEN_H)
		tmp = c->draw.wall_height / 2 - SCREEN_H / 2 - 1;
	while (++i < c->draw.wall_height)
	{
		column[i] = find_txt_pixel_color(txt, (int)c->draw.txt_x,
				(int)(tmp * scale));
		tmp++;
	}
	i = -1;		
	while (++i < c->draw.draw_start)
		my_mlx_pixel_put(&c->img, x, i,
			find_color(c->draw.c[0], c->draw.c[1], c->draw.c[2]));
	j = 0;
	while (c->draw.draw_start < c->draw.draw_end)
		my_mlx_pixel_put(&c->img, x, c->draw.draw_start++, column[j++]);
	while (c->draw.draw_end < SCREEN_H)
		my_mlx_pixel_put(&c->img, x, c->draw.draw_end++,
			find_color(c->draw.f[0], c->draw.f[1], c->draw.f[2]));
	free(column);
	return (0);
}

void	loop_ray(t_gameconfig *config)
{
	int		x;
	t_imge	*txt;

	x = 0;
	while (x < SCREEN_W)
	{
		find_ray(&config->ray, &config->player, x);
		ft_DDA(&config->ray, config->map);
		get_ply_wall_dist(&config->ray, &config->player);
		get_draw_info(&config->draw, &config->ray);
		txt = find_txt_side(config);
		find_wall_x(config, txt);
		if (x < 50)
			print_all_data(config, x);
		put_pixel_col(config, txt, x);
		x++;
	}
}

void	display(t_gameconfig *config, t_imge *img)
{
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
	display(config, img);
	mlx_hook(config->mlx_w, KeyPress, KeyPressMask, key_hook, config);
	mlx_hook(config->mlx_w, 17, 0, mouse_hook, config);
	mlx_loop(config->mlx);
}
