/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:32:34 by yachen            #+#    #+#             */
/*   Updated: 2024/02/29 15:44:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	find_wall_x(t_gameconfig *c, t_imge *txt)
{
	if (c->ray.side == 0)
		c->draw.wall_x = c->player.pos_y + c->ray.p_w_dist * c->ray.ray_y;
	else
		c->draw.wall_x = c->player.pos_x + c->ray.p_w_dist * c->ray.ray_x;
	c->draw.wall_x -= floor(c->draw.wall_x);
	c->draw.txt_x = c->draw.wall_x * txt->width;
	if (c->ray.side == 0 && c->ray.ray_x > 0)
		c->draw.txt_x = txt->width - c->draw.txt_x - 1;
	if (c->ray.side == 1 && c->ray.ray_y < 0)
		c->draw.txt_x = txt->width - c->draw.txt_x - 1;
}

t_imge	*find_txt_side(t_gameconfig *c)
{
	if (c->ray.hit == 2 && c->door == 0)
		return (c->draw.do_close);
	if (c->ray.hit == 2 && c->door == 1)
		return (c->draw.do_open);
	if (c->ray.side == 1)
	{
		if (c->ray.ray_y < 0)
			return (c->draw.txt_we);
		else
			return (c->draw.txt_ea);
	}
	else
	{
		if (c->ray.ray_x < 0)
			return (c->draw.txt_no);
		else
			return (c->draw.txt_so);
	}
	return (NULL);
}

int	find_txt_pixel_color(t_imge *txt, int x, int y)
{
	int		*color;
	int		i;

	i = (y * txt->ll) / 4 + x;
	color = (int *)txt->addr;
	return (color[i]);
}

int	*store_pixel_color_column(t_gameconfig *c, t_imge *txt)
{
	double	scale;
	int		*tmp;
	int		i;
	double	y;

	tmp = (int *)malloc(sizeof(int) * c->draw.wall_height);
	if (!tmp)
		return (NULL);
	scale = 1.0 * txt->height / c->draw.wall_height;
	y = 0;
	if (c->draw.wall_height > SCREEN_H)
		y = (c->draw.wall_height - SCREEN_H) / 2;
	i = -1;
	while (++i < c->draw.wall_height)
	{
		tmp[i] = find_txt_pixel_color(txt, (int)c->draw.txt_x,
				(int)(y * scale));
		y++;
		if ((int)(y * scale) >= txt->height)
			break ;
	}
	return (tmp);
}
