/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:32:34 by yachen            #+#    #+#             */
/*   Updated: 2024/02/22 16:14:49 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	find_pixel_color_in_txt(t_gameconfig *config, t_draw *d, t_imge *txt)
{
	double	wall_x;
	double	wall_y;
	double	tmp;
	float	scale;
	
	wall_x = modf(config->ray.side_x, &tmp) * (double)config->draw.wall_height;
	wall_y = modf(config->ray.side_y, &tmp) * (double)config->draw.wall_height;
	printf("%f | %f\n", modf(config->ray.side_x, &tmp), modf(config->ray.side_y, &tmp));

	scale = (float)txt->height / (float)config->draw.wall_height;
	d->pix_x = (int)(wall_x * scale);
	d->pix_y = (int)(wall_y * scale);
	printf("pix_x: %d\npix_y: %d\nwall_x: %f\nwall_y: %f\nscale: %f\n", d->pix_x, d->pix_y, wall_x, wall_y, scale);
}

int	convert_chars_to_int(char c1, char c2, char c3)
{
	int	color;

	color = 0;
	color |= ((unsigned char)c1);
    color = color << 8 | ((unsigned char)c2);
    color = color << 8 | ((unsigned char)c3);
	return (color);
}

