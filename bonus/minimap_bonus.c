/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:23:14 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/03/01 16:38:04 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	create_box(t_imge *img, int x, int y, int color)
{
	int	box_x;
	int	box_y;
	int	end_x;
	int	end_y;

	box_x = 20 + img->box_size * x;
	end_x = box_x + img->box_size;
	box_y = 20 + img->box_size * y;
	end_y = box_y + img->box_size;
	while (box_x < end_x)
	{
		box_y = 20 + img->box_size * y;
		while (box_y < end_y)
		{
			my_mlx_pixel_put(img, box_x, box_y, color);
			box_y++;
		}
		box_x++;
	}
}

int	find_minimap_box_scale(char **map, int x, int y)
{
	int	x_max;
	int	y_max;

	x_max = x;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (x_max < x)
				x_max = x;
		}
	}
	y_max = y;
	x = 20;
	while (x_max * x > SCREEN_W - 20)
		x--;
	y = 20;
	while (y_max * y > SCREEN_H - 20)
		y--;
	if (x * y_max < SCREEN_W - 20)
		return (x);
	return (y);
}

void	create_minimap(t_player *p, char **map, t_imge *img)
{
	int	x;
	int	y;

	y = 0;
	img->box_size = find_minimap_box_scale(map, -1, -1);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == p->start_pos)
				create_box(img, x, y, find_color(255, 255, 255));
			if (map[y][x] == '0' || map[y][x] == '2')
				create_box(img, x, y, find_color(0, 128, 255));
			if (map[y][x] == '1')
				create_box(img, x, y, find_color(0, 51, 102));
			if (map[y][x] == '3')
				create_box(img, x, y, find_color(0, 0, 0));
			x++;
		}
		y++;
	}
}
