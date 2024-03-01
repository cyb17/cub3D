/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_mouse_hook_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:19:18 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/03/01 15:52:17 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	mouse_hook(void *param)
{
	t_gameconfig	*game;

	game = (t_gameconfig *)param;
	garbage_collector(game);
	exit (0);
}

void	check_door(t_gameconfig *config, t_player *p)
{
	p->mov_x = p->pos_x + p->dir_x;
	p->mov_y = p->pos_y + p->dir_y;
	update_movex_or_movey(p);
	if (config->map[(int)p->mov_x][(int)p->pos_y] == '2')
		config->map[(int)p->mov_x][(int)p->pos_y] = '3';
	else if (config->map[(int)p->pos_x][(int)p->mov_y] == '2')
		config->map[(int)p->pos_x][(int)p->mov_y] = '3';
	else if (config->map[(int)p->mov_x][(int)p->pos_y] == '3')
		config->map[(int)p->mov_x][(int)p->pos_y] = '2';
	else if (config->map[(int)p->pos_x][(int)p->mov_y] == '3')
		config->map[(int)p->pos_x][(int)p->mov_y] = '2';
	display(config, &config->img);
}

void	minimap_hook(int keysym, t_gameconfig *config, t_player *p)
{
	if ((int)p->old_posx != (int)p->pos_x || (int)p->old_posy != (int)p->pos_y)
	{
		config->map[(int)p->old_posx][(int)p->old_posy] = p->old_c;
		if (config->map[(int)p->pos_x][(int)p->pos_y] != p->start_pos)
		{
			p->old_c = config->map[(int)p->pos_x][(int)p->pos_y];
			config->map[(int)p->pos_x][(int)p->pos_y] = p->start_pos;
		}
	}
	if (keysym == XK_m)
	{
		if (config->minimap == 0)
			config->minimap = 1;
		else
			config->minimap = 0;
	}
}

int	key_hook(int keysym, t_gameconfig *config)
{
	t_player	*p;

	p = &config->player;
	p->old_posx = p->pos_x;
	p->old_posy = p->pos_y;
	if (keysym == XK_Escape)
	{
		garbage_collector(config);
		exit(0);
	}
	rotation_camera(keysym, config, p);
	move_player_ns(keysym, config, p);
	move_player_we(keysym, config, p);
	minimap_hook(keysym, config, p);
	if (keysym == XK_space)
		check_door(config, &config->player);
	if (keysym == XK_w || keysym == XK_s || keysym == XK_a
		|| keysym == XK_d || keysym == XK_m)
		display(config, &config->img);
	return (0);
}
