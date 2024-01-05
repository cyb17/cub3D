/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:11 by yachen            #+#    #+#             */
/*   Updated: 2024/01/05 17:19:17 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// return a fd if is a valid .cub file
int	check_file_path(char *gamefile)
{
	int		fd;
	int		len;

	len = ft_strlen(gamefile);
	if (gamefile[len - 1] == 'b' && gamefile[len - 2] == 'u'
		&& gamefile[len - 3] == 'c' && gamefile[len - 4] == '.')
	{
		fd = open(gamefile, O_RDONLY);
		if (fd == -1)
		{
			perror("Error:\nOpen description file failed\n");
			return (-1);
		}
	}
	else
	{
		ft_putstr_fd("Error:\nWrong map extension\n", 2);
		return (-1);
	}
	return (fd);
}

int	check_map_position(int fd)
{
	char	*tmp;
	
	while (1)
	{
		tmp = get_next_line(fd);
	}
}

int	parsing(char *gamefile)
{
	int			fd;
	
	fd = check_file_path(gamefile);
	if (fd == -1)
		return (-1);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
		{
			ft_putstr_fd("Error: parsing: get_next_line\n", 2);
			return (-1);
		}
	}

}
