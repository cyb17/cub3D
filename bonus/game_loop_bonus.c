/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:28:47 by yachen            #+#    #+#             */
/*   Updated: 2024/02/29 12:50:11 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	put_pixel_col(t_gameconfig *c, t_imge *txt, int x)
{
	double	scale;
	int		*column;
	int		i;
	int		j;
	double	k;

	column = (int *)malloc(sizeof(int) * c->draw.wall_height);
	if (!column)
		return (err("Error!\n", "Malloc failed: put_pixel_col\n", ""));
	scale = 1.0 * txt->height / c->draw.wall_height;
	if (c->draw.wall_height > SCREEN_H)
		k = (c->draw.wall_height - SCREEN_H) / 2;
	else
		k = 0;
	i = -1;
	while (++i < c->draw.wall_height)
	{
		column[i] = find_txt_pixel_color(txt, (int)c->draw.txt_x,
				(int)(k * scale));
		k++;
		if ((int)(k * scale) >= txt->height)
			break ;
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
		put_pixel_col(config, txt, x);
		x++;
	}
}

void	display(t_gameconfig *config, t_imge *img)
{
	loop_ray(config);
	if (config->minimap == 1)
		create_minicard(&config->player, config->map, img);
	mlx_put_image_to_window(config->mlx, config->mlx_w, img->img, 0, 0);
}

void	game_loop(t_gameconfig *config, t_imge *img)
{
	config->mlx = mlx_init();
	config->mlx_w = mlx_new_window(config->mlx, SCREEN_W, SCREEN_H,
			"cub3D bonus");
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
