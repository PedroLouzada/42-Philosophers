/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:53:54 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/24 19:12:44 by pbongiov         ###   ########.fr       */
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
		if (!timer_check(table, &table->philo[i]))
			break ;
		pthread_mutex_lock(&table->finished_mutex);
		if (table->has_finished == table->heads)
		{
			pthread_mutex_unlock(&table->finished_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->finished_mutex);
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
	if (!print_msg(philo, "take a fork"))
	{
		pthread_mutex_unlock(&table->forks[philo->left]);
		return ;
	}
	pthread_mutex_lock(&table->forks[philo->right]);
	if (!print_msg(philo, "take a fork"))
	{
		pthread_mutex_unlock(&table->forks[philo->left]);
		pthread_mutex_unlock(&table->forks[philo->right]);
		return ;
	}
	update_time(table, philo);
	if (!print_msg(philo, "is eating"))
	{
		pthread_mutex_unlock(&table->forks[philo->right]);
		pthread_mutex_unlock(&table->forks[philo->left]);
		return ;
	}
	my_sleep(table->time_to_eat);
	pthread_mutex_unlock(&table->forks[philo->right]);
	pthread_mutex_unlock(&table->forks[philo->left]);
}

static void	ph_sleep(t_table *table, t_philo *philo)
{
	if (!print_msg(philo, "is sleeping"))
		return ;
	my_sleep(table->time_to_sleep);
}

static void	ph_think(t_philo *philo, int think)
{
	if (think < 10)
		return ;
	if (!print_msg(philo, "is thinking"))
		return ;
	my_sleep(think);
}

void	*routine(t_philo *philo)
{
	int		think;
	t_table	*table;

	table = philo->table;
	think = table->time_to_die - (table->time_to_eat + table->time_to_sleep);
	pthread_mutex_lock(&philo->live_mutex);
	philo->time_to_live = get_time() + table->time_to_die;
	if (table->heads % 2 == 0)
	{
		if (philo->index % 2 != 0)
			my_sleep(table->time_to_eat);
	}
	pthread_mutex_unlock(&philo->live_mutex);
	while (1)
	{
		ph_eat(table, philo);
		if (!finish_check(table, philo))
			break ;
		ph_sleep(table, philo);
		ph_think(philo, think);
	}
	return (NULL);
}
