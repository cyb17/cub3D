/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_imge_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:03 by yachen            #+#    #+#             */
/*   Updated: 2024/02/29 15:36:47 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

t_imge	*load_img(void *mlx, char *path)
{
	t_imge	*img;

	if (!mlx)
		return (NULL);
	img = (t_imge *)malloc(sizeof(t_imge));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (img->img == NULL)
	{
		ft_putstr_fd("Error: mlx_xpm_file_to_image\n", 2);
		free(img);
		return (NULL);
	}
	return (img);
}

int	load_all_texture(t_gameconfig *config, t_draw *d)
{
	d->txt_no = load_img(config->mlx, config->no);
	if (!d->txt_no)
		return (err("load texture NO failed\n", "", ""));
	d->txt_so = load_img(config->mlx, config->so);
	if (!d->txt_so)
		return (err("load texture SO failed\n", "", ""));
	d->txt_we = load_img(config->mlx, config->we);
	if (!d->txt_we)
		return (err("load texture WE failed\n", "", ""));
	d->txt_ea = load_img(config->mlx, config->ea);
	if (!d->txt_ea)
		return (err("load texture EA failed\n", "", ""));
	d->do_open = load_img(config->mlx, "./textures/door_open.xpm");
	if (!d->do_open)
		return (err("load door_open failed\n", "", ""));
	d->do_close = load_img(config->mlx, "./textures/door_close.xpm");
	if (!d->do_close)
		return (err("load door_close failed\n", "", ""));
	d->txt_no->addr = mlx_get_data_addr(d->txt_no->img, &d->txt_no->bpp, &d->txt_no->ll, &d->txt_no->ed);
	d->txt_so->addr = mlx_get_data_addr(d->txt_so->img, &d->txt_so->bpp, &d->txt_so->ll, &d->txt_so->ed);
	d->txt_we->addr = mlx_get_data_addr(d->txt_we->img, &d->txt_we->bpp, &d->txt_we->ll, &d->txt_we->ed);
	d->txt_ea->addr = mlx_get_data_addr(d->txt_ea->img, &d->txt_ea->bpp, &d->txt_ea->ll, &d->txt_ea->ed);
	d->do_open->addr = mlx_get_data_addr(d->do_open->img, &d->do_open->bpp, &d->do_open->ll, &d->do_open->ed);
	d->do_close->addr = mlx_get_data_addr(d->do_close->img, &d->do_close->bpp, &d->do_close->ll, &d->do_close->ed);
	return (0);
}
