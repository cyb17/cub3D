/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:11 by yachen            #+#    #+#             */
/*   Updated: 2024/01/06 12:10:19 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
			perror("Error:\nDescription file path not valid\n");
			return (-1);
		}
		close(fd);
	}
	else
	{
		ft_putstr_fd("Error:\nWrong map extension\n", 2);
		return (-1);
	}
	return (0);
}

// int	is_map_line(char *str)
// {
// 	int	i;

// 	while (str[i] && (str[i] == ' ' || ((str[i] > 8 && str[i] < 14))))
// 		i++;
// 	while (str[i])
// 	{
// 		if (str[i] != '1' && str[i] != '0' && str[i] != 'N'
// 		&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
// 	}
// }

// int	check_map_position(char *gamefile)
// {
// 	int		fd;
// 	char	*tmp;
	
// 	fd = open(gamefile, O_RDONLY);
// 	while (1)
// 	{
// 		tmp = get_next_line(fd);
// 	}
// }

// char	**get_config_info(char *gamefile)
// {
// 	int		fd;
// 	int		size;
// 	char	*tmp;
// 	char	**first_rd;

// 	fd = open(gamefile, O_RDONLY);
// 	size = 0;
// 	while (1)
// 	{
// 		tmp = get_next_line(fd);
// 		if (tmp && tmp[0] != '\n' && tmp[0] != '\0')
// 	}
// }


// check if element found had a correct nb of follow info
int	check_element(char *line, t_gameconfig *config)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (!tmp)
	{
		ft_putstr_fd("Error:\nParsing: check_element: split malloc failed\n", 2);
		return (-1);
	}
	if (tmp[2] != NULL)
	{
		ft_putstr_fd("Error:\nToo much follow information behind element id\n", 2);
		free_tab(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

// check if the existence of this no element is authorized by the subject
int	check_line(char *line)
{
	
}

void	analyze_line(char *line, t_gameconfig *config)
{
	int	i;
	int	rslt;

	i = 0;
	rslt = 0;
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		rslt = check_element(line, config);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		rslt = check_element(line, config);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		rslt = check_element(line, config);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		rslt = check_element(line, config);
	else if (line[0] == 'F' && line[1] == ' ')
		rslt = check_element(line, config);
	else if (line[0] == 'C' && line[1] == ' ')
		rslt = check_element(line, config);
	else
		rslt = check_line(line);
	return (rslt)
}

void	get_config_info(char *gamefile, t_gameconfig *config)
{
	int		fd;
	char	*tmp;

	fd = open(gamefile, O_RDONLY);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		else
		{
			analyze_line(tmp, config);
			free(tmp);
		}
	}
}

int	parsing(char *gamefile, t_gameconfig *config)
{
	char	**first_rd;
	
	if (check_file_path(gamefile) == -1)
		return (-1);
}
