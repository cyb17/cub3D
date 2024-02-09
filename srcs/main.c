/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:28 by yachen            #+#    #+#             */
/*   Updated: 2024/02/09 12:00:16 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_imge *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	game_loop(t_gameconfig *game, t_imge *img)
{
	game->mlx = mlx_init();
	game->mlx_w = mlx_new_window(game->mlx, 640, 480, "cub3D");
	img->img = mlx_new_image(game->mlx, 640, 480);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->ed);
	my_mlx_pixel_put(img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(game->mlx, game->mlx_w, img->img, 0, 0);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_gameconfig	config;

	init_gameconfig(&config);
	if (argc == 2 && argv[1] && argv[1][0] != '\0')
	{
		if (check_gamefile(argv[1], &config) != 0)
			return (1);
		game_loop(&config, &config.img);
	}
	else
		ft_putstr_fd("Error!\nParameter not valid\n", 2);
	return (0);
}
