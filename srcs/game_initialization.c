/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:47 by yachen            #+#    #+#             */
/*   Updated: 2024/02/14 11:47:57 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_gameconfig(t_gameconfig *config)
{
	config->file = NULL;
	config->map = NULL;
	config->mlx = NULL;
	config->mlx_w = NULL;
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->f = NULL;
	config->c = NULL;
	config->nb_element = 0;
	config->player.pos_x = 0.0;
	config->player.pos_y = 0.0;
	config->player.dir_x = -1;
	config->player.dir_y = 0;
	config->player.plane_x = 0;
	config->player.plane_y = 0;
	config->player.camera_x = 0;
	config->img.img = NULL;
	config->img.addr = NULL;
	config->img.bpp = 0;
	config->img.ll = 0;
	config->img.ed = 0;
}

void	update_gameconfig(t_gameconfig *config)
{
	find_start_position(config);
	if_start_pos_found(config);
}
