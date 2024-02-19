/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_mouse_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:19:18 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/02/19 18:05:47 by yachen           ###   ########.fr       */
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

	p = &config->player;
	if (keysym == XK_Escape)
	{
		garbage_collector(config);
		exit(0);
	}
	if (keysym == XK_d)
	{
		if(config->map[(int)(p->pos_x - p->dir_y * MOV_SPEED)][(int)(p->pos_y)] == '0')
			p->pos_x += p->dir_y * MOV_SPEED;
      	if(config->map[(int)(p->pos_x)][(int)(p->pos_y + p->dir_x * MOV_SPEED)] == '0')
			p->pos_y += p->dir_x * MOV_SPEED;
		display(config, &config->img);
	}
	else if (keysym == XK_a)
	{
		if(config->map[(int)(p->pos_x + p->dir_y * MOV_SPEED)][(int)(p->pos_y)] == '0')
			p->pos_x -= p->dir_y * MOV_SPEED;
      	if(config->map[(int)(p->pos_x)][(int)(p->pos_y - p->dir_x * MOV_SPEED)] == '0')
			p->pos_y -= p->dir_x * MOV_SPEED;
		display(config, &config->img);
	}
	else if (keysym == XK_w)
	{
		printf("ok1\n");
		if(config->map[(int)(p->pos_x + p->dir_x * MOV_SPEED)][(int)(p->pos_y)] == '0')
			p->pos_x += p->dir_x * MOV_SPEED;
      	if(config->map[(int)(p->pos_x)][(int)(p->pos_y + p->dir_y * MOV_SPEED)] == '0')
			p->pos_y += p->dir_y * MOV_SPEED;
		display(config, &config->img);
	}
	else if (keysym == XK_s)
	{
		printf("ok2\n");
		if(config->map[(int)(p->pos_x - p->dir_x * MOV_SPEED)][(int)(p->pos_y)] == '0')
			p->pos_x -= p->dir_x * MOV_SPEED;
      	if(config->map[(int)(p->pos_x)][(int)(p->pos_y - p->dir_y * MOV_SPEED)] == '0')
			p->pos_y -= p->dir_y * MOV_SPEED;
		display(config, &config->img);
	}
	return (0);
}