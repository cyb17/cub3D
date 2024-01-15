/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:11 by yachen            #+#    #+#             */
/*   Updated: 2024/01/15 12:56:32 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	err(char *msg1, char *msg2, char *msg3)
{
	int	rslt;
	
	while (*msg1)
		rslt = write(2, msg1++, 1);
	while (*msg2)
		rslt = write(2, msg2++, 1);
	while (*msg1)
		rslt = write(2, msg3++, 1);
	rslt = -1;
	return(rslt);
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
	char		*tmp;
	
	tmp = line;
	element.id = *tmp++;
	while (*tmp == ' ')
		tmp++;
	element.info = ft_strdup(tmp);
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
	if (*line == '\n')
		return (0);
	while (*line)
	{
		if (*line != '1' && *line != ' ' && *line!= '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	err_map_condition(char *line, int i, int ply_pos)
{
	if (line[i] != '1' && line[i] != '0' && line[i] != ' '
		&& line[i] != 'N' && line[i] != 'S' && line[i] == 'W' && line[i] == 'E')
		return (err("Error!\nBad map content: ", line, "\n"));	
	if (line[i] == ' ' && (line[i - 1] != '1' || line[i + 1] != '1'))
		return (err("Error!\nSpace in map: ", line, "\n"));
	if (ply_pos > 1)
		return (err("Error!\nToo much player position: ", line, "\n"));
	return (0);
}

int	check_map_content(int fd)
{
	int		i;
	char	*line;
	int		ply_pos;

	ply_pos = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (line[i] && (line[i] == ' ' || ((line[i] > 8 && line[i] < 14))))
			i++;
		while (line[i])
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
				ply_pos++;
			if (err_map_condition(line, i, ply_pos) == -1)
				return (-1);
			i++;
		}
		free(line);
	}
	if (ply_pos == 0)
		return (err("Error!\n", "Player position missing\n", NULL));
	return (0);
}

// int	put_map_in_tab(t_gameconfig *config)
// {
// 	t_map	*tmp;
// 	int		size;
// 	char	**map;
// 	int		i;
	
// 	tmp = config->map;
// 	while (*tmp)
// 	{
// 		size++;
// 		tmp = tmp->next;
// 	}
// 	map = (char **)malloc(sizeof(char *) * size);
// 	if (!map)
// 		return(err("Error!\nParsing: Put_map_in_tab:", "malloc failed", "\n"));
// 	tmp = config->map;
// 	i = 0
// 	while (*tmp)
// 	{
// 		config->tab[i++] = tmp->line;
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	make_map(int fd, t_gameconfig *config)
// {
// 	t_map	*tmp;

// 	tmp = config->map;
// 	while (1)
// 	{
// 		tmp->line = get_next_line(fd);
// 		if (!tmp->line)
// 			break ;
// 		tmp = tmp->next;		
// 	}
// 	tmp->next = NULL;
// 	put_map_in_tab(config);
// }

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
		else if (is_empty_line(line))
			rslt = 0;
		else if (is_start_map(line))
		{
			if (config->nb_element != 6 || make_map(fd, config) == -1)
		//		|| check_map_content(fd) == -1)
				rslt = -1;
		}
		else
			rslt = err("Error!\nBad element: ", line, NULL);
		if (rslt == -1)
		{
			free(line);
			garbage_collector(config);
			return ;
		}
	}
}

// int	get_map_size(char *gamefile)
// {
// 	int		size;
// 	int		fd;
// 	char	*line;

// 	size = 0;
// 	fd = open(gamefile, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error: get_map_size\n");
// 		ft_putstr_fd(gamefile, 2);
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		if (is_start_map(line))
// 		{
// 			while (line)
// 			{
// 				line = get_next_line(fd);
// 				size++;
// 				free(line);
// 			}
// 			break ;
// 		}
// 	}
// 	return (size);
// }

// int	get_map(char *gamefile, t_gameconfig *config)
// {
// 	int		fd;
// 	int		size;
// 	char	*line;
// 	char	**map;

// 	fd = check_file_path(gamefile)
// 	if (fd == -1)
// 	{
// 		garbage_collector(config);
// 		return (-1);
// 	}
// 	size = get_map_size(gamefile)
// 	if (size == -1)
// 	{
// 		garbage_collector(config);
// 		close (fd);
// 		return (-1);
// 	}
// 	config->map->mapptr = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!config->map->mapptr)
// 	{
// 		garbage_collector(config);
// 		close (fd);
// 		return (-1);
// 	}
// 	map = config->map->mapptr;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		if (is_start_map(line))
// 		{
// 			*map = line;
// 			while (*map)
// 			{
// 				map++;
// 				*map = get_next_line(fd);
// 			}
// 		}
// 	}
// }

int	parsing(char *gamefile, t_gameconfig *config)
{
	int				fd;
	
	fd = check_file_path(gamefile);
	if (fd == -1)
		return (-1);
	first_read_file(fd, config);
	if (config->nb_element != 6)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
