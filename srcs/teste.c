/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:36:14 by yachen            #+#    #+#             */
/*   Updated: 2024/01/15 16:53:36 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libft/get_next_line.h"
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

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("t.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
}
