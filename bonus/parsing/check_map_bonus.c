/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:43:27 by yachen            #+#    #+#             */
/*   Updated: 2024/02/23 17:46:56 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int error_cases(char **map, int row, int col, int *ply_pos)
{
	if (map[row][col] == '\t')
	{
		ft_putstr_fd("Error!\nDetecting tabulation in map part\n", 2);
		ft_putstr_fd("Please, replace it by spaces and try again\n", 2);
		return (-1);
	}
	if (map[row][col] != ' ' && map[row][col] != '1'
		&& map[row][col] != '0' && map[row][col] != 'N' && map[row][col] != 'S'
		&& map[row][col] != 'W' && map[row][col] != 'E')
		return (err("Error!\nWrong map content: ", map[row], "\n"));
	if (map[row][col] == 'N' || map[row][col] == 'S' || map[row][col] == 'W'
		|| map[row][col] == 'E')
		(*ply_pos)++;
	if (*ply_pos > 1)
		return (err("Error!\nThere is too many player in map\n", "",""));
	return (0);
}

int	check_wall(char **map, int size)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				&& (!is_surrounded_by_walls(map, size, i, j)))
				return (err("Error!\nMap not closed or space in map\n", "", ""));
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_content(char **map, int size)
{
	int	row;
	int	col;
	int	ply_pos;

	row = 0;
	ply_pos = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col] && map[row][col] != '\n')
		{
			if (error_cases(map, row, col, &ply_pos) == -1)
				return (-1);
			col++;
		}
		row++;
	}
	if (ply_pos == 0)
		return (err("Error!\nPlayer position missing\n", "",""));
	return (check_wall(map, size));
}

int	check_gameconfig_content(t_gameconfig *config)
{
	if (!config->file)
	{
		err("Error!\n", "Empty file\n", "");
		return (-1);
	}
	if (!config->no || !config->so || !config->we || !config->ea
		|| !config->f || !config->c || !config->map)
	{
		ft_putstr_fd("Error!\nGame configuration not complete\n", 2);
		ft_putstr_fd("Please check again\n", 2);
		return (-1);
	}
	return (0);
}
