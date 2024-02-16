/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:19:18 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/02/16 09:05:02 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	shut_down_game(void *param)
{
	t_gameconfig	*game;

	game = (t_gameconfig *)param;
	garbage_collector(game);
	return (0);
}
