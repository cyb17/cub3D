/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:11:48 by yachen            #+#    #+#             */
/*   Updated: 2024/01/15 18:18:32 by yachen           ###   ########.fr       */
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

int	get_info_from_list(t_gameconfig *config)
{
	int		rslt;
	t_list	*tmp;
	
	rslt = 0;
	tmp = config->file;
	while (tmp)
	{
		if (is_element(tmp->content))
			rslt = put_to_element(tmp->content, config);
		else if (is_empty_line(tmp->content))
			rslt = 0;
		else if (is_start_map(tmp->content) && config->nb_element == 6)
			return (0);//rslt = make_map();
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
	// while (config->file)
	// {
	// 	printf("%s", (char *)config->file->content);
	// 	config->file = config->file->next;
	// }
	// first_read_file(fd, config, gamefile);
	// if (config->nb_element != 6)
	// {
	// 	close(fd);
	// 	return (-1);
	// }
	// close(fd);
	return (0);
}