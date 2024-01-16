/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:08:53 by yachen            #+#    #+#             */
/*   Updated: 2024/01/16 13:35:28 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// static void	free_element(t_element *element, t_gameconfig *config)
// {
// 	if (element->info)
// 		free(element->info);
// 	if (element->img)
// 	{
// 		mlx_destroy_image(config->mlx, element->img);
// 		free(element->img);
// 	}
// }

// static void	free_map(t_map *map)
// {
// 	if (map)
// 	{
// 		if (map->mlx_w)
// 			mlx_destroy_window(map->mlx, map->mlx_w);
// 		if (map->mlx)
// 			mlx_destroy_display(map->mlx);
// 		if (map->mlx)
// 			free(map->mlx);
// 		if (map->mapptr)
// 			free_tab(map->mapptr);
// 		if (map)
// 			free(map);
// 	}
// }

void	clear_list_ptr(t_list **list)
{
	t_list	*tmp;
	
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

void	garbage_collector(t_gameconfig *config)
{
	if (config->file)
		clear_list_ptr(&config->file);
	// if (config->no)
	// 	free_element(config->no, config->mlx);
	// if (config->so)
	// 	free_element(config->so, config->mlx);
	// if (config->we)
	// 	free_element(config->we, config->mlx);
	// if (config->ea)
	// 	free_element(config->ea, config->mlx);
	// if (config->f)
	// 	free_element(config->f, config->mlx);
	// if (config->c)
	// 	free_element(config->c, config->mlx);
	// config->nb_element = 0;
	// free_tab(config->map);
}
