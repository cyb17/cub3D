/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:28 by yachen            #+#    #+#             */
/*   Updated: 2024/02/18 12:29:22 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv, char **env)
{
	t_gameconfig	config;

	if (env && !env[0])
		return (err("Error!\n", "Environement NULL", "\n"));
	init_gameconfig(&config);
	if (argc == 2 && argv[1] && argv[1][0] != '\0')
	{
		if (check_gamefile(argv[1], &config) != 0)
			return (1);
		update_gameconfig(&config);
		game_loop(&config, &config.img);
	}
	else
		ft_putstr_fd("Error!\nParameter not valid\n", 2);
	return (0);
}
