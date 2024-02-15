/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:36:15 by yachen            #+#    #+#             */
/*   Updated: 2024/02/15 17:09:43 by yachen           ###   ########.fr       */
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
