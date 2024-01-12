/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:11 by yachen            #+#    #+#             */
/*   Updated: 2024/01/12 18:33:39 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	err(char *msg1, char *msg2, char *msg3)
{
	while (*msg1)
		write(2, msg1++, 1);
	while (*msg2)
		write(2, msg2++, 1);
	while (*msg1)
		write(2, msg3++, 1);
	return(-1);
}

// check if is a valid .cub file
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
			perror("Error:\n");
			ft_putstr_fd(gamefile, 2);
			return (-1);
		}
	}
	else
	{
		err("Error!\nWrong map extension: ", gamefile, "\n");
		return (-1);
	}
	return (fd);
}

// check element id and nb of followed info
int	is_element(char *line)
{
	char	*tmp;
	int		nb_info;

	tmp = line;
	nb_info = 0;
	while (*tmp)
	{
		if (*tmp == ' ' && *(tmp + 1) != ' ' && *(tmp + 1))
			nb_info++;
		tmp++;	
	}
	if (((line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		&& line[1] == ' ' && nb_info == 1)
		|| ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ' && nb_info >= 1
			&& nb_info < 4))
		return (1);
	return (0);
}

// put to element if element not already exist
int	put_to_element(char *line, t_gameconfig *config)
{
	t_element	element;
	
	element.id = *line++;
	while (*line == ' ')
		line++;
	element.info = ft_strdup(line);
	if (!element.info)
		return (err("Error!\n", line, "\nput_to_element: malloc failed\n"));
	element.img = NULL;
	if (line[0] == 'N' && !config->no)
		config->no = &element;
	else if (line[0] == 'S' && !config->so)
		config->so = &element;
	else if (line[0] == 'W' && !config->we)
		config->we = &element;
	else if (line[0] == 'E' && !config->ea)
		config->ea = &element;
	else if (line[0] == 'F' && !config->f)
		config->f = &element;
	else if (line[0] == 'C' && !config->c)
		config->c = &element;
	else
		return (err("Error!\nElement already present: ", line, "\n"));
	config->nb_element++;
	return (0);
}

int	is_start_map(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n');
			return (0);
		line++;
	}
	return (1);
}

int	err_map_condition(char *line, int i)
{
	if (line[i] != '1' && line[i] != '0' && line[i] != ' '
		&& line[i] != 'N' && line[i] != 'S' && line[i] == 'W' && line[i] == 'E')
		return (err("Error!\nBad map content: ", line, "\n"));	
	if (line[i] == ' ' && (line[i - 1] != '1' || line[i + 1] != '1'))
		return (err("Error!\nSpace in map: ", line, "\n"));
	if (ply_pos > 1)
		return (err("Error!\nToo much player position: ", line, "\n"));
}

int	check_map_content(int fd)
{
	int		i;
	char	*line;
	int		ply_pos;

	i = 0;
	ply_pos = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[i] && (line[i] == ' ' || ((line[i] > 8 && line[i] < 14))))
			i++;
		while (line[i])
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
				ply_pos++;
			if (err_map_condition(line, i) == -1)
				return (-1);
			i++;
		}
	}
	if (ply_pos == 0)
		return (err("Error!\n", "Player position missing\n", NULL));
	return (0);
}

// get configuration elements and if there is a map, check it content 
void	first_read_file(int fd, t_gameconfig *config)
{
	int				rslt;
	char			*line;

	rslt = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_element(line))
			rslt = put_to_element(line, config);
		else if (is_start_map(line) && (config.nb_element != 6
			|| check_map_content(fd) == -1))
			rslt = -1;
		else if (is_empty_line(line) == 0)
			rslt = err("Error!\nBad element: ", line, NULL);	
		free(line);
		if (rslt == -1)
		{
			garbage_collector(config);
			return ;
		}
	}
}

int	get_map_size(char *gamefile)
{
	int		size;
	int		fd;
	char	*line;

	size = 0;
	fd = open(gamefile, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: get_map_size\n");
		ft_putstr_fd(gamefile, 2);
		return (-1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_start_map(line))
		{
			while (1)
			{
				line = get_next_line(fd);
				size++;
				free(line);
			}
		}
	}
}

int	get_map(char *gamefile, t_gameconfig *config)
{
	int		fd;
	char	*line;

	fd = check_file_path(gamefile)
	if (fd == -1)
	{
		garbage_collector(config);
		return (-1);
	}
	while (1)
	{
		
	}
}

int	parsing(char *gamefile, t_gameconfig *config)
{
	int				fd;
	
	fd = check_file_path(gamefile)
	if (fd == -1)
		return (-1);
	first_read_file(fd, config);
	if (config->nb_element != 6 || get_map(gamefile, config) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
