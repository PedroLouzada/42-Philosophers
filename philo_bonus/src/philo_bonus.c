/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:35:44 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/23 20:42:25 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

int main(int ac, char **av)
{
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
	process_create(&table);
	while (i < table->heads)

	
	table->forks = sem_open("/forks", O_CREATE, 0644, 5);
	sem_post (fporks)

	sem_wait(table->forks)
	
	sem_close(forks);
	// sem_unlink("/forks");
}