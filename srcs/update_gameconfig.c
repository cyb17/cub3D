/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gameconfig.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:25:02 by yachen            #+#    #+#             */
/*   Updated: 2024/02/18 12:28:23 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	get_c_or_f_info(char *str, int tab[3])
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == ','))
		i++;
	tab[0] = ft_atoi(str + i);
	while (ft_isdigit(str[i]) != 0)
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == ','))
		i++;
	tab[1] = ft_atoi(str + i);
	while (ft_isdigit(str[i]) != 0)
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == ','))
		i++;
	tab[2] = ft_atoi(str + i);
}

void	update_gameconfig(t_gameconfig *config)
{
	find_start_position(config);
	if_start_pos_found(config);
	// find_ray(&config->ray, &config->player);
	// ft_DDA(&config->ray, config->map);
	// get_ply_wall_dist(&config->ray);
	// get_draw_info(&config->draw, &config->ray);
	get_c_or_f_info(config->c, config->draw.c);
	get_c_or_f_info(config->f, config->draw.f);
}