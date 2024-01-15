/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:28 by yachen            #+#    #+#             */
/*   Updated: 2024/01/15 17:30:54 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_config(t_gameconfig *config)
{
	config->file = NULL;
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->f = NULL;
	config->c = NULL;
	config->nb_element = 0;
	config->map = NULL;
}

int	main(int argc, char **argv)
{
	t_gameconfig	config;
	
	init_config(&config);
	if (argc == 2 && argv[1] && argv[1][0] != '\0')
	{
		if (parsing(argv[1], &config) == 0)
			printf("parsing ok\n");
	}
	else
		ft_putstr_fd("Error!\nParameter not valid\n", 2);
	return (0);
}