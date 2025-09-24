/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:35:44 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/24 15:52:23 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

int	main(int ac, char **av)
{
	int res;
	int i;
	t_table table;

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
	process_create(&table);
	if (table.my_pid == 0)
		routine(&table);
	else
	{
		i = 0;
		while (i < table.heads)
		{
			waitpid(table.child_pid[i], NULL, 0);
			i++;
		}
		sem_close(table.eaters);
		sem_unlink("/eaters");
		sem_close(table.forks);
		sem_unlink("/forks");
	}
}
