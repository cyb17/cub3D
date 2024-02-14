/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:08:53 by yachen            #+#    #+#             */
/*   Updated: 2024/02/14 16:43:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	destroye_img(t_gameconfig *config, t_draw *d)
{
	if (d->txt_no.img)
		mlx_destroy_image(config->mlx, d->txt_no.img);
	if (d->txt_so.img)
		mlx_destroy_image(config->mlx, d->txt_so.img);
	if (d->txt_we.img)
		mlx_destroy_image(config->mlx, d->txt_we.img);
	if (d->txt_ea.img)
		mlx_destroy_image(config->mlx, d->txt_ea.img);
	if (d->txt_no.addr)
		free(d->txt_no.addr);
	if (d->txt_so.addr)
		free(d->txt_so.addr);
	if (d->txt_we.addr)
		free(d->txt_we.addr);
	if (d->txt_ea.addr)
		free(d->txt_ea.addr);
}

// void	free_img_ptr(t_gameconfig *config)
// {
// 	if (config->draw->txt_no)
// 		free(config->draw->txt_no);
// 	if (config->draw->txt_so)
// 		free(config->draw->txt_so);
// 	if (config->draw->txt_we)
// 		free(config->draw->txt_we);
// 	if (config->draw->txt_ea)
// 		free(config->draw->txt_ea);
// }

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
	// free_img_ptr(config);
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
