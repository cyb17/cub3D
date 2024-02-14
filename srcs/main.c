/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:28 by yachen            #+#    #+#             */
/*   Updated: 2024/02/14 17:15:27 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_gameconfig(t_gameconfig *config)
{
	find_start_position(config);
	if_start_pos_found(config);
	find_ray(&config->ray, &config->player);
	ft_DDA(&config->ray, config->map);
	get_ply_wall_dist(&config->ray);
	get_draw_info(&config->draw, &config->ray);
	get_c_code(config->c, &config->draw);
	get_f_code(config->f, &config->draw);
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


void	put_floor_and_ceiling_to_window(int c[3], int f[3], t_imge *img)
{
	int	floor;
	int ceiling;
	int	x;
	int	y;

	floor = find_color(f[0], f[1], f[2]);
	ceiling = find_color(c[0], c[1], c[2]);
	printf("%d %d\n",f[0], c[0]);
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

void	game_loop(t_gameconfig *config, t_imge *img)
{
	config->mlx = mlx_init();
	config->mlx_w = mlx_new_window(config->mlx, SCREEN_W, SCREEN_H, "cub3D");
	img->img = mlx_new_image(config->mlx, SCREEN_W, SCREEN_H);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->ed);
	//my_mlx_pixel_put(img, 5, 5, 0x00FF0000); boucle : calculer le point/mur et colori la colone
	put_floor_and_ceiling_to_window(config->draw.c, config->draw.f, img);
	mlx_put_image_to_window(config->mlx, config->mlx_w, img->img, 0, 0);
	mlx_loop(config->mlx);
}

int	main(int argc, char **argv, char **env)
{
	t_gameconfig	config;

	if (env && !env[0])
		return (err("Error!\n", "Environement NULL", "\n"));
	init_gameconfig(&config);
	if (argc == 2 && argv[1] && argv[1][0] != '\0')
	{
		if (check_gamefile(argv[1], &config) != 0)
			return (1);
		update_gameconfig(&config);
		game_loop(&config, &config.img);
	}
	else
		ft_putstr_fd("Error!\nParameter not valid\n", 2);
	return (0);
}
