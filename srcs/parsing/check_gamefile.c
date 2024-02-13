/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gamefile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:11:48 by yachen            #+#    #+#             */
/*   Updated: 2024/02/13 10:11:02 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
			perror("Error!\n");
			err(gamefile, "\n", "");
			return (-1);
		}
	}
	else
	{
		err("Error!\nBad map extension: ", gamefile, "\n");
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

int	make_map(t_list *start, char ***map)
{
	int		i;
	int		size;

	size = find_size(start);
	*map = (char **)malloc(sizeof(char *) * (size + 1));
	if (!*map)
		return (err("Error!\n","Make_map: ", "Malloc failed\n"));
	i = 0;
	while (start)
	{
		if (!is_empty_line(start->content))
			(*map)[i++] = start->content;
		else
		{
			while (start && is_empty_line(start->content))
				start = start->next;
			if (start != NULL)
				return (err("Error\nToo much information after map description\n", "", ""));
		}
		if (start)
			start = start->next;
	}
	(*map)[i] = NULL;
	return (check_map_content(*map, size));
}

int	get_info_from_list(t_gameconfig *config)
{
	int		rslt;
	t_list	*tmp;
	
	rslt = 0;
	tmp = config->file;
	while (tmp)
	{
		if (is_element(tmp->content) && !element_already_present(tmp->content, config))
			rslt = 0;
		else if (is_empty_line(tmp->content))
			rslt = 0;
		else if (is_start_map(tmp->content) && config->nb_element == 6)
			return (make_map(tmp, &config->map)); 
		else
			rslt = -1;
		if (rslt == -1)
		{
			ft_putstr_fd("Error!\nNot correct element or bad map position ", 2);
			ft_putstr_fd("or a element is missing : ", 2);
			return (err((char *)tmp->content, "Please check again\n", ""));
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_gamefile(char *gamefile, t_gameconfig *config)
{
	int	fd;
	
	fd = check_file_path(gamefile);
	if (fd == -1)
		return (-1);
	read_file_to_list(fd, config);
	if (get_info_from_list(config) == -1
		|| check_gameconfig_content(config) == -1)
	{
		garbage_collector(config);
		return (-1);
	}
	// t_list	*tmp = config->file;
	// while (tmp)
	// {
	// 	printf("%s\n", (char *)tmp->content);
	// 	tmp = tmp->next;
	// }
	// int	i = 0;
	// while (config->map[i])
	// 	printf("map:%s\n", config->map[i++]);
	return (0);
}