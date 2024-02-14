/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_imge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:03 by yachen            #+#    #+#             */
/*   Updated: 2024/02/14 17:04:58 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_ply_wall_dist(t_ray *r)
{
	if(r->side == 0) 
		r->p_w_dist = (r->side_x - r->delta_x);
    else
	  r->p_w_dist = (r->side_y - r->delta_y);
}

void	get_draw_info(t_draw *d, t_ray *r)
{
	d->wall_height = SCREEN_H / r->p_w_dist;
	d->draw_start = SCREEN_H / 2 - d->wall_height / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = SCREEN_H / 2 + d->wall_height / 2;
	if (d->draw_end >= SCREEN_H)
		d->draw_end = SCREEN_H - 1;
}

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
		free(img);
		return (NULL);
	}
	return (img);
}

int	load_all_texture(t_gameconfig *config, t_draw *d)
{
	d->txt_no = load_img(config->mlx, "../textures/north.png");
	d->txt_so = load_img(config->mlx, "../textures/south.png");
	d->txt_we = load_img(config->mlx, "../textures/west.png");
	d->txt_ea = load_img(config->mlx, "../textures/east.png");
	if (!d->txt_no || !d->txt_so || !d->txt_we || !d->txt_ea)
		return (err("Error!\n", "loading texture failed", ""));
	return (0);
}

void	get_c_code(char *c, t_draw *d)
{
	int	i;

	i = 0;
	while (c[i] && (c[i] == ' ' || c[i] == '\t' || c[i] == ','))
		i++;
	d->c[0] = ft_atoi(c + i);
	while (ft_isdigit(c[i]) != 0)
		i++;
	while (c[i] && (c[i] == ' ' || c[i] == '\t' || c[i] == ','))
		i++;
	d->c[1] = ft_atoi(c + i);
	while (ft_isdigit(c[i]) != 0)
		i++;
	while (c[i] && (c[i] == ' ' || c[i] == '\t' || c[i] == ','))
		i++;
	d->c[2] = ft_atoi(c + i);
}

void	get_f_code(char *f, t_draw *d)
{
	int	i;

	i = 0;
	while (f[i] && (f[i] == ' ' || f[i] == '\t' || f[i] == ','))
		i++;
	d->f[0] = ft_atoi(f + i);
	while (ft_isdigit(f[i]) != 0)
		i++;
	while (f[i] && (f[i] == ' ' || f[i] == '\t' || f[i] == ','))
		i++;
	d->f[1] = ft_atoi(f + i);
	while (ft_isdigit(f[i]) != 0)
		i++;
	while (f[i] && (f[i] == ' ' || f[i] == '\t' || f[i] == ','))
		i++;
	d->f[2] = ft_atoi(f + i);
}
