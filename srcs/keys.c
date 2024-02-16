/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:19:18 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/02/16 10:54:33 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	shut_down_game(void *param)
{
	t_gameconfig	*game;

	game = (t_gameconfig *)param;
	garbage_collector(game);
	exit (0);
}
