/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:36:14 by yachen            #+#    #+#             */
/*   Updated: 2024/01/12 16:10:54 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (-1);
}

int	is_element(char *line)
{
	char	*tmp;
	int		nb_info;

	tmp = line;
	nb_info = 0;
	while (*tmp)
	{
		if (*tmp == ' ' && *(tmp + 1) != ' ' && *(tmp + 1))
			nb_info++;
		tmp++;
	}
	if (((line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
			&& line[1] == ' ' && nb_info == 1)
		|| ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ' && nb_info >= 1
			&& nb_info < 4))
		return (1);
	return (0);
}

int	main(void)
{
	printf("rslt = %d\n", is_element("C 200,54,45"));
	return (err("error\n"));
}
