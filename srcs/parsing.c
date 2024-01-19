/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:11:48 by yachen            #+#    #+#             */
/*   Updated: 2024/01/19 17:53:06 by yachen           ###   ########.fr       */
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

void	read_file_to_list(int fd, t_gameconfig *config)
{
	t_list	*tmp;

	while (1)
	{
		tmp = ft_lstnew(get_next_line(fd));
		if (!tmp)
			break ;
		ft_lstadd_back(&config->file, tmp);
	}
	close(fd);
}

int	check_info(char *tmp)
{
	int	i;
	
	i = 0;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	while(tmp[i] && tmp[i] != ',' && tmp[i] != '\n')
	{
		if (!ft_isdigit(tmp[i]))
			return (err("Error!\nColor code has to be digit: ", tmp, "\n"));
		i++;
	}
	(*tmp)[i] = '\0';
	if (ft_atoi(tmp) < 0  || ft_atoi(tmp) > 255)
		return (err("Error!\nColor code has to be between 0-255: ", tmp, "\n"));
	return (0);
}

int	with_correct_info(char *line)
{
	char	**tab;
	char	**tmp;
	int		i;

	tab = ft_split(line, ',');
	if (!tab)
		return (err("Error!\nWith_correct_info: Malloc failed\n", "", ""));
	tmp = tab;
	while (*tmp)
	{
		if (ft_strlen(*tmp) > 4 || check_info(*tmp) == -1)
		{
			free_tab(tab);
			return (0);
		}
		tmp++;
	}
	free_tab(tab);
	return (1);
}

int	is_element(char *line)
{
	char	*tmp;

	tmp = line;
	if ((line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E'
		|| line[0] == 'C' || line[0] == 'F') && (line[1] == ' ' || line[1] == '\t'))
	{
		tmp++;
		while (*tmp && (*tmp == ' ' || *tmp == '\t'))
			tmp++;	
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		{
			while (*tmp)
			{
				if (*tmp == ' ' || *tmp == '\t')
					return (0);
				tmp++;
			}
			return (1);
		}
		else if ((line[0] == 'C' || line[0] == 'F') && with_correct_info(tmp, ft_strlen(tmp)))
			return (1);
	}
	return (0);
}

// put to element if element not already exist
int	put_to_element(char *line, char *line2, t_gameconfig *config)
{
	t_element	element;
	
	element.id = *line2++;
	while (*line2 == ' ')
		line2++;
	element.info = ft_strdup(line2);
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

int	have_right_wall(char **map, int i, int j)
{
	while (map[i][j] && map[i][j] != '\n')
	{
		if (map[i][j] == '1')
			return (1);
		j++;
	}
	return (0);
}

int	have_left_wall(char **map, int i, int j)
{
	while (j >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		j--;
	}
	return (0);
}

int	have_top_wall(char **map, int i, int j)
{
	while (i >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		i--;
	}
	return (0);
}

int	have_bottom_wall(char **map, int i, int j, int size)
{
	while (i < size)
	{
		if (map[i][j] == '1')
			return (1);
		i++;
	}
	return (0);
}

int	is_surrounded_by_walls(char **map, int size, int i, int j)
{
	if (have_right_wall(map, i, j) && have_left_wall(map, i, j)
		&& have_top_wall(map, i, j) && have_bottom_wall(map, i, j, size))
		return (1);
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
				|| map[i][j] == 'W' || map[i][j] == 'E') && (!is_surrounded_by_walls(map, size, i, j)))
				return (err("Error!\nMap not closed in the line\n", map[i], "\n"));
			if (map[i][j] == ' ' && is_surrounded_by_walls(map, size, i, j))
				return (err("Error!\nSpace in map in the line\n", map[i], "\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int error_cases(char **map, int row, int col, int *ply_pos)
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

int	check_map(char **map, int size)
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

int	find_map_size(t_list *start)
{
	int		size;

	size = 0;
	while (start)
	{
		start = start->next;
		size++;
	}
	return (size);
}

int	make_map(t_list *start, t_gameconfig *config)
{
	int		i;
	int		size;

	size = find_map_size(start);
	config->map = (char **)malloc(sizeof(char *) * (size + 1));
	if (!config)
		return (err("Error!\n","Make_map: ", "Malloc failed\n"));
	i = 0;
	while (start)
	{
		if (!is_empty_line(start->content))
			config->map[i++] = start->content;
		else
		{
			while (start && is_empty_line(start->content))
				start = start->next;
			if (start != NULL)
				return (err("Error\nToo much information after map description", "", ""));
		}
		if (start)
			start = start->next;
	}
	config->map[i] = NULL;
	return (check_map(config->map, size));
}

int	get_info_from_list(t_gameconfig *config)
{
	int		rslt;
	t_list	*tmp;
	
	rslt = 0;
	tmp = config->file;
	while (tmp)
	{
		if (is_element(tmp->content))
			rslt = put_to_element(tmp->content, tmp->content, config);
		else if (is_empty_line(tmp->content))
			rslt = 0;
		else if (is_start_map(tmp->content) && config->nb_element == 6)
			return (make_map(tmp, config)); 
		else
			rslt = -1;
		if (rslt == -1)
		{
			ft_putstr_fd("Error!\nThis line is not correct: ", 2);
			return (err((char *)tmp->content, "\nPlease check again\n", ""));
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parsing(char *gamefile, t_gameconfig *config)
{
	int	fd;
	
	fd = check_file_path(gamefile);
	if (fd == -1)
		return (-1);
	read_file_to_list(fd, config);
	if (get_info_from_list(config) == -1)
	{
		garbage_collector(config);
		return (-1);
	}
	return (0);
}