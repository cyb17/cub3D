/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:09:22 by jp-de-to          #+#    #+#             */
/*   Updated: 2024/02/14 13:11:20 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	if_start_pos_found(t_gameconfig *config)
{
	if (config->player.start_pos == 'N')
	{
		config->player.dir_x = -1;
		config->player.plane_y = 0.66;
	}
	if (config->player.start_pos == 'S')
	{
		config->player.dir_x = 1;
		config->player.plane_y = -0.66;
	}
	if (config->player.start_pos == 'W')
	{
		config->player.dir_y = -1;
		config->player.plane_x = -0.66;
	}
	if (config->player.start_pos == 'E')
	{
		config->player.dir_y = 1;
		config->player.plane_x = 0.66;
	}
}

void	find_start_position(t_gameconfig *config)
{
	char	**map;
	int		x;
	int		y;

	y = -1;
	map = config->map;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
			|| map[y][x] == 'W')
			{
				config->player.start_pos = map[y][x];
				config->player.pos_x = x + 0.5;
				config->player.pos_y = y + 0.5;
				break ;
			}
		}
	}
}

char	*ft_strim_path(char *path)
{
	char	*tmp;
	int		i;
	int		j;
	int 	k;

	i = 1;
	j = ft_strlen(path) - 1;
	tmp = path;
	while (path[i] && (path[i] == ' ' || path[i] == '\t'))
		i++;
	while (path[j] && (path[j] == ' ' || path[j] == '\t'))
		j--;
	k = 0;
	while (i <= j)
		tmp[k++] = path[i++];
	tmp[k] = '\0';
	return (tmp);
}

