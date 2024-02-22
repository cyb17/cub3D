/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_mouse_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:19:18 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/02/22 16:14:26 by jp-de-to         ###   ########.fr       */
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

void	rotation_camera(int keysym, t_gameconfig *config, t_player *p)
{
	double	dir_ref;
	double	plane_ref;

	dir_ref = p->dir_x;
	plane_ref = p->plane_x;
	if (keysym == XK_Right)
	{
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = dir_ref * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y
			* sin(-ROT_SPEED);
		p->plane_y = plane_ref * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
		display(config, &config->img);
	}
	else if (keysym == XK_Left)
	{
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = dir_ref * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = plane_ref * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
		display(config, &config->img);
	}
}

void	move_player_NS(int keysym, t_gameconfig *config, t_player *p)
{
	double		map_x;
	double		map_y;

	if (keysym == XK_w)
	{
		map_x = p->pos_x + (p->dir_x * MOV_SPEED);
		map_y = p->pos_y + (p->dir_y * MOV_SPEED);
		if (p->dir_x < 0 && map_x < p->pos_x)
			map_x -= MOV_SPEED;
		if (p->dir_x > 0 && map_x > p->pos_x)
			map_x += MOV_SPEED;
		if (p->dir_y > 0 && map_y > p->pos_y)
			map_y += MOV_SPEED;
		if (p->dir_y < 0 && map_y < p->pos_y)
			map_y -= MOV_SPEED;
		if (config->map[(int)map_x][(int)p->pos_y] == '0'
			|| config->map[(int)map_x][(int)p->pos_y] == p->start_pos)
			p->pos_x += p->dir_x * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)map_y] == '0'
			|| config->map[(int)p->pos_x][(int)map_y] == p->start_pos)
			p->pos_y += p->dir_y * MOV_SPEED;
		display(config, &config->img);
	}
	else if (keysym == XK_s)
	{
		map_x = (p->pos_x - (p->dir_x * MOV_SPEED));
		map_y = (p->pos_y - (p->dir_y * MOV_SPEED));
		if (config->map[(int)map_x][(int)p->pos_y] == '0'
			|| config->map[(int)map_x][(int)p->pos_y] == p->start_pos)
			p->pos_x -= p->dir_x * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)map_y] == '0'
			|| config->map[(int)p->pos_x][(int)map_y] == p->start_pos)
			p->pos_y -= p->dir_y * MOV_SPEED;
		display(config, &config->img);
	}
}

void	move_player_WE(int keysym, t_gameconfig *config, t_player *p)
{
	double		map_x;
	double		map_y;

	if (keysym == XK_a)
	{
		map_x = (p->pos_x - (p->dir_y * MOV_SPEED));
		map_y = (p->pos_y + (p->dir_x * MOV_SPEED));
		if (p->dir_x < 0 && map_y < p->pos_y)
			map_y -= MOV_SPEED;
		if (p->dir_y > 0 && map_x < p->pos_x)
			map_x -= MOV_SPEED;
		if (p->dir_y < 0 && map_x < p->pos_x)
			map_x -= MOV_SPEED;
		if (config->map[(int)map_x][(int)p->pos_y] == '0'
			|| config->map[(int)map_x][(int)p->pos_y] == p->start_pos)
			p->pos_x -= p->dir_y * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)map_y] == '0'
			|| config->map[(int)p->pos_x][(int)map_y] == p->start_pos)
			p->pos_y += p->dir_x * MOV_SPEED;
		display(config, &config->img);
	}
	else if (keysym == XK_d)
	{
		map_x = (p->pos_x + (p->dir_y * MOV_SPEED));
		map_y = (p->pos_y - (p->dir_x * MOV_SPEED));
		if (config->map[(int)map_x][(int)map_y] == '0'
			|| config->map[(int)map_x][(int)map_y] == p->start_pos)
			p->pos_x += p->dir_y * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)map_y] == '0'
			|| config->map[(int)p->pos_x][(int)map_y] == p->start_pos)
			p->pos_y -= p->dir_x * MOV_SPEED;
		display(config, &config->img);
	}
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
	rotation_camera(keysym, config, p);
	move_player_NS(keysym, config, p);
	move_player_WE(keysym, config, p);
	return (0);
}
