/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:46:00 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/26 17:31:19 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	static int i;

	i = 0;
	//printf("arg: %d\n", philo->index);
	//sleep(5);
	return NULL;
}

int main(int ac, char **av)
{
	static t_table table;
	int i;
	int n;
	
	if (ac < 5 || ac > 6)
		return (0);
	i = 0;
	data_init(&table, av);
	printf("Forks: %d\n", table.forks);
	printf("Die  : %lld\n", table.time_to_die);
	printf("Eat  : %lld\n", table.time_to_eat);
	printf("Sleep: %lld\n", table.time_to_sleep);
	while (i < table.forks)
	{
		table.philo[i].table = &table;
		table.philo[i].index = i;
		pthread_create(&table.philo[i].thread_id, NULL, (void *)routine, &table.philo[i]);
		i++;
	}
	i = 0;
	while (i < table.forks)
		pthread_join(table.philo[i++].thread_id, NULL);
	free(table.philo);
	//sleep(10);
}
