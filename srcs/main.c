/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:28 by yachen            #+#    #+#             */
/*   Updated: 2024/02/14 14:04:47 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_gameconfig(t_gameconfig *config)
{
	find_start_position(config);
	if_start_pos_found(config);
	find_ray(config->ray,config->player);
	ft_DDA(config->ray, config->map);
	get_ply_wall_dist(config->ray);
	get_draw_info(config->draw, config->ray);
	
}

void	my_mlx_pixel_put(t_imge *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	game_loop(t_gameconfig *config, t_imge *img)
{
	config->mlx = mlx_init();
	config->mlx_w = mlx_new_window(config->mlx, SCREEN_W, SCREEN_H, "cub3D");
	img->img = mlx_new_image(config->mlx, SCREEN_W, SCREEN_H);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->ed);
	//my_mlx_pixel_put(img, 5, 5, 0x00FF0000); boucle : calculer le point/mur et colori la colone
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
