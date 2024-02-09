/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:47 by yachen            #+#    #+#             */
/*   Updated: 2024/02/09 14:28:26 by yachen           ###   ########.fr       */
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
	config->player.pos_x = 0;
	config->player.pos_y = 0;
	config->player.dir_x = -1;
	config->player.dir_y = 0;
	config->player.plane = 0;
	config->player.plane = 0.66;
	config->player.camera_x = 0;
	config->player.camera_y = 0;
	config->img.img = NULL;
	config->img.addr = NULL;
	config->img.bpp = 0;
	config->img.ll = 0;
	config->img.ed = 0;
}
