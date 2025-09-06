/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:53:54 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/07 00:44:45 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*die(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (1)
	{
		time_passed(table);
		pthread_mutex_lock(&table->philo[i].last_meal_mutex);
		if (get_time() > table->philo[i].time_to_live)
		{
			while (j < table->heads)
			{
				pthread_mutex_destroy(&table->philo[j].last_meal_mutex);
				pthread_mutex_destroy(&table->forks[j++]);
			}
			my_sleep(9);
			print_msg(&table->philo[i], "died");
			free(table->philo);
			free(table->forks);
			exit(0); 
		}
		pthread_mutex_unlock(&table->philo[i].last_meal_mutex);
		i++;	
		if (i >= table->heads)
			i = 0;
		usleep(500);
	}
	return (NULL);
}

static void	ph_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->left]);
	print_msg(philo, "take a fork");
	pthread_mutex_lock(&table->forks[philo->right]);
	print_msg(philo, "take a fork");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->time_to_live = get_time() + table->time_to_die;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	print_msg(philo, "is eating");
	my_sleep(table->time_to_eat);
	pthread_mutex_unlock(&table->forks[philo->right]);
	pthread_mutex_unlock(&table->forks[philo->left]);
}

static void	ph_sleep(t_table *table, t_philo *philo)
{
	time_passed(table);
	print_msg(philo, "is sleeping");
	my_sleep(table->time_to_sleep);
}

static void ph_think(t_table *table, t_philo *philo)
{
	time_passed(table);
	if (table->time_to_die - (table->time_to_eat + table->time_to_sleep) - 100 < 100)
	 	return;
	print_msg(philo, "is thinking");
	my_sleep(table->time_to_die - (table->time_to_eat + table->time_to_sleep) - 100);
}

void	*routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->time_to_live = get_time() + table->time_to_die;
	while (1)
	{
		ph_eat(table, philo);
		ph_sleep(table, philo);
		ph_think(table, philo);
	}
	return (NULL);
}
