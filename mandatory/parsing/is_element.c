/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_element.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:38:01 by yachen            #+#    #+#             */
/*   Updated: 2024/02/14 13:10:37 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	element_already_present(char *line, t_gameconfig *config)
{
	if (line[0] == 'N' && config->no == NULL)
		config->no = ft_strim_path(line);
	else if (line[0] == 'S' && config->so == NULL)
		config->so = ft_strim_path(line);
	else if (line[0] == 'W' && config->we == NULL)
		config->we = ft_strim_path(line);
	else if (line[0] == 'E' && config->ea == NULL)
		config->ea = ft_strim_path(line);
	else if (line[0] == 'F' && config->f == NULL)
		config->f = ft_strim_path(line);
	else if (line[0] == 'C' && config->c == NULL)
		config->c = ft_strim_path(line);
	else
	{
		err("Error!\nElement already present: ", line, "\n");
		return (1);
	}
	config->nb_element++;
	return (0);
}

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
