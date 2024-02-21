/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_mouse_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:19:18 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/02/21 16:52:29 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	mouse_hook(void *param)
{
	t_gameconfig	*game;

	game = (t_gameconfig *)param;
	garbage_collector(game);
	exit (0);
}

int	key_hook(int keysym, t_gameconfig *config)
{
	t_player	*p;
	double		 map_x;
	double	 	map_y;

	p = &config->player;
	if (keysym == XK_Escape)
	{
		garbage_collector(config);
		exit(0);
	}
	if (keysym == XK_w)
	{
		map_x = (p->pos_x + (p->dir_x * MOV_SPEED)); //- 0.5);
		map_y = (p->pos_y + (p->dir_y * MOV_SPEED)); //- 0.5);
		if (config->map[(int)map_x][(int)p->pos_y] == '0' || config->map[(int)map_x][(int)p->pos_y] == p->start_pos)
			p->pos_x += p->dir_x * MOV_SPEED;
		display(config, &config->img);
	}
	else if (keysym == XK_s)
	{
		map_x = (p->pos_x - (p->dir_x * MOV_SPEED) - 0.5);
		map_y = (p->pos_y - (p->dir_y * MOV_SPEED) - 0.5);
		if(config->map[(int)map_x][(int)p->pos_y] == '0' || config->map[(int)map_x][(int)p->pos_y] == p->start_pos)
			p->pos_x -= p->dir_x * MOV_SPEED;
		display(config, &config->img);
	}
	else if (keysym == XK_a)
	{
		map_x = (p->pos_x + (p->dir_y * MOV_SPEED)); //- 0.5);
		map_y = (p->pos_y + (p->dir_x * MOV_SPEED)); //- 0.5);
		if (config->map[(int)p->pos_x][(int)map_y] == '0' || config->map[(int)p->pos_x][(int)map_y] == p->start_pos)
			p->pos_y += p->dir_x * MOV_SPEED;
		display(config, &config->img);
	}
	else if (keysym == XK_d)
	{
		map_x = (p->pos_x - (p->dir_y * MOV_SPEED) - 0.5);
		map_y = (p->pos_y - (p->dir_x * MOV_SPEED) - 0.5);
		printf("dir_y = %f | dir_x = %f\n", p->dir_y, p->dir_x);
		printf("pos_y = %f | pos_x = %f\n", p->pos_y, p->pos_x);
		printf("map_y = %f | map_x = %f\n", map_y, map_x);
		printf("caractere = %c\n", config->map[(int)map_x][(int)p->pos_y]);
		if (config->map[(int)p->pos_x][(int)map_y] == '0' || config->map[(int)p->pos_x][(int)map_y] == p->start_pos)
		{
			printf("ok\n");
			p->pos_y -= p->dir_x * MOV_SPEED;
			printf("pos_x = %f\n", p->pos_x);
		}
		display(config, &config->img);
	}
	return (0);
}
