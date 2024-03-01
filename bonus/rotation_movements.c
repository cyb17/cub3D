/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:35:49 by yachen            #+#    #+#             */
/*   Updated: 2024/03/01 14:37:49 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

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

void	update_movex_or_movey(t_player *p)
{
	if (p->pos_x > p->mov_x && (int)p->mov_x == (int)p->pos_x
		&& ((double)(p->mov_x - (int)p->mov_x) == (double)0))
		p->mov_x -= 1;
	if (p->pos_y > p->mov_y && (int)p->mov_y == (int)p->pos_y
		&& ((double)(p->mov_y - (int)p->mov_y) == (double)0))
		p->mov_y -= 1;
}

void	get_player_mov(t_player *p, int i)
{
	if (i == 1)
	{
		p->mov_x = p->pos_x + (p->dir_x * MOV_SPEED);
		p->mov_y = p->pos_y + (p->dir_y * MOV_SPEED);
		update_movex_or_movey(p);
	}
	else
	{
		p->mov_x = p->pos_x - (p->dir_x * MOV_SPEED);
		p->mov_y = p->pos_y - (p->dir_y * MOV_SPEED);
		update_movex_or_movey(p);
	}
}

void	move_player_ns(int keysym, t_gameconfig *config, t_player *p)
{
	if (keysym == XK_w)
	{
		get_player_mov(p, 1);
		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0'
			|| config->map[(int)p->mov_x][(int)p->pos_y] == p->start_pos
			|| config->map[(int)p->mov_x][(int)p->pos_y] == '2')
			p->pos_x += p->dir_x * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0'
			|| config->map[(int)p->pos_x][(int)p->mov_y] == p->start_pos
			|| config->map[(int)p->pos_x][(int)p->mov_y] == '2')
			p->pos_y += p->dir_y * MOV_SPEED;
	}
	else if (keysym == XK_s)
	{
		get_player_mov(p, 0);
		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0'
			|| config->map[(int)p->mov_x][(int)p->pos_y] == p->start_pos)
			p->pos_x -= p->dir_x * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0'
			|| config->map[(int)p->pos_x][(int)p->mov_y] == p->start_pos)
			p->pos_y -= p->dir_y * MOV_SPEED;
	}
}

void	move_player_we(int keysym, t_gameconfig *config, t_player *p)
{
	if (keysym == XK_a)
	{
		p->mov_x = p->pos_x - (p->dir_y * MOV_SPEED);
		p->mov_y = p->pos_y + (p->dir_x * MOV_SPEED);
		update_movex_or_movey(p);
		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0'
			|| config->map[(int)p->mov_x][(int)p->pos_y] == p->start_pos)
			p->pos_x -= p->dir_y * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0'
			|| config->map[(int)p->pos_x][(int)p->mov_y] == p->start_pos)
			p->pos_y += p->dir_x * MOV_SPEED;
	}
	else if (keysym == XK_d)
	{
		p->mov_x = (p->pos_x + (p->dir_y * MOV_SPEED));
		p->mov_y = (p->pos_y - (p->dir_x * MOV_SPEED));
		update_movex_or_movey(p);
		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0'
			|| config->map[(int)p->mov_x][(int)p->pos_y] == p->start_pos)
			p->pos_x += p->dir_y * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0'
			|| config->map[(int)p->pos_x][(int)p->mov_y] == p->start_pos)
			p->pos_y -= p->dir_x * MOV_SPEED;
	}
}
