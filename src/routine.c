/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:53:54 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/31 20:19:06 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*die(t_table *table)
{
	int i; 
	static long current_time;
	
	i = 0;
	while(1)
	{
		current_time = get_time();
		if (current_time - table->philo[i].last_meal >= table->time_to_die)
		{
			i = 0;
			while (i < table->heads)
			{
				pthread_detach(table->philo[i].thread_id);
				i++;
			}
			free(table->philo);
			free(table->forks);
			printf("%ld %i died\n", table->time, table->philo[i].index + 1);
			exit(0);
		}
		if (i >= table->heads - 1)
			i = 0;
	}
	return (NULL);
}

static void	eat(t_table *table, t_philo *philo)
{
	int	left;
	int	right;

	left = philo->index - 1;
	right = (philo->index) % table->heads;
	pthread_mutex_lock(&table->forks[left]);
	printf("%ld %i take a fork\n", table->time, philo->index);
	pthread_mutex_lock(&table->forks[right]);
	printf("%ld %i take a fork\n", table->time, philo->index);
	printf("%ld %i is eating\n", table->time, philo->index);
	philo->last_meal = get_time();
	usleep(table->time_to_eat);
	pthread_mutex_unlock(&table->forks[right]);
	pthread_mutex_unlock(&table->forks[left]);
}

static void	ph_sleep(t_table *table, t_philo *philo)
{
	time_passed(table);
	printf("%ld %i is sleeping\n", table->time, philo->index);
	usleep(table->time_to_sleep);
}
void	*routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	while (1)
	{
		eat(table, philo);
		ph_sleep(table, philo);
	}
	return (NULL);
}
