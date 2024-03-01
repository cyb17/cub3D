/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:08:53 by yachen            #+#    #+#             */
/*   Updated: 2024/03/01 12:05:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	destroye_img(t_gameconfig *config, t_draw *d)
{
	if (d->txt_no)
		mlx_destroy_image(config->mlx, d->txt_no->img);
	if (d->txt_so)
		mlx_destroy_image(config->mlx, d->txt_so->img);
	if (d->txt_we)
		mlx_destroy_image(config->mlx, d->txt_we->img);
	if (d->txt_ea)
		mlx_destroy_image(config->mlx, d->txt_ea->img);
}

void	free_img_ptr(t_gameconfig *config)
{
	if (config->draw.txt_no)
		free(config->draw.txt_no);
	if (config->draw.txt_so)
		free(config->draw.txt_so);
	if (config->draw.txt_we)
		free(config->draw.txt_we);
	if (config->draw.txt_ea)
		free(config->draw.txt_ea);
}

void	clear_list_ptr(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

void	garbage_collector(t_gameconfig *config)
{
	destroye_img(config, &config->draw);
	free_img_ptr(config);
	if (config->img.img)
		mlx_destroy_image(config->mlx, config->img.img);
	if (config->mlx_w)
		mlx_destroy_window(config->mlx, config->mlx_w);
	if (config->mlx)
	{
		mlx_destroy_display(config->mlx);
		free(config->mlx);
	}
	if (config->file)
		clear_list_ptr(&config->file);
	free(config->map);
}
