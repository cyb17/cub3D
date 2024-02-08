/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:47 by yachen            #+#    #+#             */
/*   Updated: 2024/02/08 14:41:27 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_config(t_gameconfig *config)
{
	config->file = NULL;
	config->no = 0;
	config->so = 0;
	config->we = 0;
	config->ea = 0;
	config->f = 0;
	config->c = 0;
	config->nb_element = 0;
	config->map = NULL;
	config->player = NULL;
}
