/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_element.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:38:01 by yachen            #+#    #+#             */
/*   Updated: 2024/02/08 15:45:20 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	check_info(char *tmp)
{
	int	i;
	int	start_digit;
	int	end_digit;

	i = 0;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	start_digit = i;
	while (tmp[i] && ft_isdigit(tmp[i]))
		i++;
	end_digit = i;
	if (start_digit == end_digit)
		return (err("Error!\n", "Bad information\n", ""));
	while (tmp[i])
	{
		if (tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != ',' && tmp[i] != '\n')
			return (err("Error!\n", "Bad information", "\n"));
		i++;
	}
	tmp[end_digit] = '\0';
	if (ft_atoi(tmp + start_digit) < 0  || ft_atoi(tmp + start_digit) > 255)
		return (err("Error!\nColor code has to be between 0-255\n", "", ""));
	return (0);
}
	
int	element_already_present(char *line, t_gameconfig *config)
{
	if (line[0] == 'N' && config->no == 0)
		config->no = 1;
	else if (line[0] == 'S' && config->so == 0)
		config->so = 1;
	else if (line[0] == 'W' && config->we == 0)
		config->we = 1;
	else if (line[0] == 'E' && config->ea == 0)
		config->ea = 1;
	else if (line[0] == 'F' && config->f == 0)
		config->f = 1;
	else if (line[0] == 'C' && config->c == 0)
		config->c = 1;
	else
	{
		err("Error!\nElement already present: ", line, "\n");
		return (1);
	}
	config->nb_element++;
	return (0);
}

int	with_correct_info(char *line)
{
	char	**tab;
	int		i;

	tab = ft_split(line, ',');
	if (!tab)
		return (err("Error!\nWith_correct_info: Malloc failed\n", "", ""));
	i = 0;
	while (tab[i])
	{
		if (i > 2 || check_info(tab[i]) == -1)
		{
			free_tab(tab);
			return (0);
		}
		i++;
	}
	free_tab(tab);
	if (i < 3)
		return (0);
	return (1);
}

int	is_element(char *line)
{
	char	*tmp;

	line = delete_white_space(line);
	tmp = line;
	if ((line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E'
		|| line[0] == 'C' || line[0] == 'F') && (line[1] == ' ' || line[1] == '\t'))
	{
		tmp++;
		while (*tmp && (*tmp == ' ' || *tmp == '\t'))
			tmp++;	
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		{
			while (*tmp && *tmp != ' ' && *tmp != '\t')
				tmp++;
			tmp = delete_white_space(tmp);
			if (*tmp && *tmp != '\n')
				return (0);
			return (1);
		}
		else if ((line[0] == 'C' || line[0] == 'F') && with_correct_info(tmp))
			return (1);
	}
	return (0);
}

// put to element if element not already exist
// int	put_to_element(char *line, char *line2, t_gameconfig *config)
// {
// 	static t_element	element;
	
// 	line = delete_white_space(line);
// 	line2 = delete_white_space(line);
// 	element.id = *line2++;
// 	while (*line2 == ' ')
// 		line2++;
// 	element.info = line2;
// 	if (!element.info)
// 		return (err("Error!\n", line, "\nput_to_element: malloc failed\n"));
// 	element.img = NULL;
// 	if (line[0] == 'N' && !config->no)
// 		config->no = &element;
// 	else if (line[0] == 'S' && !config->so)
// 		config->so = &element;
// 	else if (line[0] == 'W' && !config->we)
// 		config->we = &element;
// 	else if (line[0] == 'E' && !config->ea)
// 		config->ea = &element;
// 	else if (line[0] == 'F' && !config->f)
// 		config->f = &element;
// 	else if (line[0] == 'C' && !config->c)
// 		config->c = &element;
// 	else
// 		return (err("Error!\nElement already present: ", line, "\n"));
// 	config->nb_element++;
// 	return (0);
// }