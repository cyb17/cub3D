/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:23:14 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/03/01 12:14:22 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	check_door(t_gameconfig *config, t_player *p)
{
	p->mov_x = p->pos_x + p->dir_x;
	p->mov_y = p->pos_y + p->dir_y;
	update_movex_or_movey(p);
	if (config->map[(int)p->mov_x][(int)p->pos_y] == '2'
		|| config->map[(int)p->pos_x][(int)p->mov_y] == '2')
	{
		if (config->door == 0)
			config->door = 1;
		else
			config->door = 0;
	}
	display(config, &config->img);
}

// Collisions des murs 

void	update_movex_or_movey(t_player *p)
{
	if (p->pos_x > p->mov_x && (int)p->mov_x == (int)p->pos_x
		&& ((double)(p->mov_x - (int)p->mov_x) == (double)0))
		p->mov_x -= 1;
	if (p->pos_y > p->mov_y && (int)p->mov_y == (int)p->pos_y
		&& ((double)(p->mov_y - (int)p->mov_y) == (double)0))
		p->mov_y -= 1;
}

// Minicarte

void	create_case(t_imge *img, int x, int y, int color)
{
	int	case_x;
	int	case_y;
	int	end_x;
	int	end_y;
	int	minimap_h;
	int	minimap_w;

	minimap_h = SCREEN_H / 60;
	minimap_w = SCREEN_W / 60;
	case_x = 30 + minimap_w * x;
	case_y = 30 + minimap_h * y;
	end_x = case_x + minimap_w;
	end_y = case_y + minimap_h;
	while (case_x < end_x)
	{
		case_y = 30 + minimap_h * y;
		while (case_y < end_y)
		{
			my_mlx_pixel_put(img, case_x, case_y, color);
			case_y++;
		}
		case_x++;
	}
}

void	create_minicard(t_player *p, char **map, t_imge *img)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == p->start_pos)
				create_case(img, x, y, find_color(255, 255, 255));
			if (map[y][x] == '0')
				create_case(img, x, y, find_color(0, 128, 255));
			if (map[y][x] == '1')
				create_case(img, x, y, find_color(0, 51, 102));
			if (map[y][x] == '2')
				create_case(img, x, y, find_color(0, 0, 0));
			x++;
		}
		y++;
	}
}
