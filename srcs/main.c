/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:18:28 by yachen            #+#    #+#             */
/*   Updated: 2024/01/06 10:20:39 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_gameconfig	config;
	
	config = NULL;
	if (argc == 2 && argv[1] && argv[1][0] != '\0')
	{
		parsing(argv[1], &config);
	}
	else
	{
		ft_putstr_fd("Error:\nParameter not valid\n", 2);
		exit(1);
	}
	return (0);
}