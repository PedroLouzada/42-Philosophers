/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:46:00 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/09 19:40:44 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	static t_table	table;
	int				i;
	int				n;

	if (ac < 5 || ac > 6)
	{
		printf("Expected: Num_of_philo / Time_to_die / Time_to_eat / Time_to_sleep\n");
		return (0);
	}
	i = 0;
	data_init(&table, av);
	if (ac == 6)
	{
		table.optional = 1;
		table.to_eat = ft_atol(av[5]);
	}
	//_debug(&table);
	while (i < table.heads)
	{
		table.philo[i].table = &table;
		pthread_create(&table.philo[i].thread_id, NULL, (void *)routine, &table.philo[i]);
		pthread_detach(table.philo[i].thread_id);
		i++;
	}
	pthread_create(&table.die_id, NULL, (void *)die, &table);
	pthread_join(table.die_id, NULL);
	i = 0;
	while (i < table.heads)
	{
		pthread_mutex_destroy(&table.philo[i].last_meal_mutex);
		pthread_mutex_destroy(&table.forks[i++]);
	}
	free(table.philo);
	free(table.forks);
}
