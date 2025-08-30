/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:46:00 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/30 18:36:58 by pbongiov         ###   ########.fr       */
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
	while (i < table.heads)
	{
		table.philo[i].table = &table;
		table.philo[i].index = i;
		pthread_create(&table.philo[i].thread_id, NULL, (void *)routine,
			&table.philo[i]);
		i++;
	}
	i = 0;
	while (i < table.heads)
		pthread_join(table.philo[i++].thread_id, NULL);
	free(table.philo);
	i = 0;
	while (i < table.heads)
		pthread_mutex_destroy(&table.philo[i++].lock);
	// sleep(10);
}
