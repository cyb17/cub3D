/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:36:14 by yachen            #+#    #+#             */
/*   Updated: 2024/01/20 11:21:52 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libft/libft.h"
// int	err(char *str)
// {
// 	while (*str)
// 		write(2, str++, 1);
// 	return (-1);
// }

// int	is_element(char *line)
// {
// 	char	*tmp;
// 	int		nb_info;

// 	tmp = line;
// 	nb_info = 0;
// 	while (*tmp)
// 	{
// 		if (*tmp == ' ' && *(tmp + 1) != ' ' && *(tmp + 1))
// 			nb_info++;
// 		tmp++;
// 	}
// 	if (((line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
// 			&& line[1] == ' ' && nb_info == 1)
// 		|| ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ' && nb_info >= 1
// 			&& nb_info < 4))
// 		return (1);
// 	return (0);
// }

int	err(char *msg1, char *msg2, char *msg3)
{
	int	rslt;
	
	while (*msg1)
		rslt = write(2, msg1++, 1);
	while (*msg2)
		rslt = write(2, msg2++, 1);
	while (*msg1)
		rslt = write(2, msg3++, 1);
	rslt = -1;
	return(rslt);
}

int	main(void)
{
	err("hfj", "fdgs", "gfh\n");
}
