/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:46:00 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/20 16:17:44 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	int		res;
	t_table	table;

	if (ac < 5 || ac > 6)
		return (printf(MSG MSG2), 0);
	res = data_init(&table, av);
	if (!res)
		return (printf("Error on memory allocation\n"), 0);
	else if (res == 2)
		return (0);
	if (ac == 6)
	{
		table.optional = 1;
		table.to_eat = ft_atol(av[5]);
	}
	thread_create(&table);
	free_stuff(&table);
}
