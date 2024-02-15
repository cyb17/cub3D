/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_imge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:03 by yachen            #+#    #+#             */
/*   Updated: 2024/02/15 17:44:20 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	d->txt_no = load_img(config->mlx, "../textures/test.xpm");
	if (!d->txt_no)
		ft_putstr_fd("failed no\n", 2);
	d->txt_so = load_img(config->mlx, "../textures/test.xpm");
	if (!d->txt_so)
		ft_putstr_fd("failed so\n", 2);
	d->txt_we = load_img(config->mlx, "../textures/test.xpm");
	if (!d->txt_we)
		ft_putstr_fd("failed we\n", 2);
	d->txt_ea = load_img(config->mlx, "../textures/test.xpm");
	if (!d->txt_ea)
		ft_putstr_fd("failed ea\n", 2);
	// if (!d->txt_no || !d->txt_so || !d->txt_we || !d->txt_ea)
		// return (err("Error!\n", "loading texture failed", ""));
	// d->txt_no->addr = mlx_get_data_addr(d->txt_no->img, &d->txt_no->bpp, &d->txt_no->ll, &d->txt_no->ed);
	// d->txt_so->addr = mlx_get_data_addr(d->txt_so->img, &d->txt_so->bpp, &d->txt_so->ll, &d->txt_so->ed);
	// d->txt_we->addr = mlx_get_data_addr(d->txt_we->img, &d->txt_we->bpp, &d->txt_we->ll, &d->txt_we->ed);
	// d->txt_ea->addr = mlx_get_data_addr(d->txt_ea->img, &d->txt_ea->bpp, &d->txt_ea->ll, &d->txt_ea->ed);
	return (0);
}
