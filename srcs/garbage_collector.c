/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:08:53 by yachen            #+#    #+#             */
/*   Updated: 2024/01/12 18:04:12 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	free_element(t_element *element, t_map *map)
{
	if (element->info)
		free(element->info);
	if (element->img)
	{
		if (element->img->imgptr)
			mlx_destroy_image(map->mlx, element->img->imgptr);
		free(element->img);
	}
}

static void	free_map(t_map *map)
{
	if (map)
	{
		if (map->mlx_w)
			mlx_destroy_window(map->mlx, map->mlx_w);
		if (map->mlx)
			mlx_destroy_display(map->mlx);
		if (map->mlx)
			free(map->mlx);
		if (map->mapptr)
			free_tab(map->mapptr);
		if (map)
			free(map);
	}
}

void	garbage_collector(t_gameconfig *src)
{
	if (src->no)
		free_element(src->no);
	if (src->so)
		free_element(src->so);
	if (src->we)
		free_element(src->we);
	if (src->ea)
		free_element(src->ea);
	if (src->f)
		free_element(src->f);
	if (src->c)
		free_element(src->c);
	src->nb_element = 0;
	free_map(src->map);
}
