/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alice <acoinus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:30:43 by alice             #+#    #+#             */
/*   Updated: 2022/02/14 11:40:18 by alice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int	tab[260];
	int	i;

	i = 0;
	while (i < 260)
		tab[i++] = 0;
	i = 0;
	while (++i < 3)
	{
		while(*av[i])
		{
			if (!tab[(int)*av[i]])
			{
				tab[(int)*av[i]] = 1;
				write(1, av[i], 1);
			}
			++av[i];
		}
	}
	write(1, "\n", 1);
	return (0);
}
