/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:53:54 by pbongiov          #+#    #+#             */
/*   Updated: 2025/10/03 19:22:45 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_check(t_table *table, t_philo *philo)
{
	size_t	time;

	time = table->time_to_eat;
	if (table->time_to_die < table->time_to_eat)
		time = table->time_to_die;
	if (philo->index % 2 != 0)
		my_sleep(time);
}

int	finished(t_table *table)
{
	pthread_mutex_lock(&table->finished_mutex);
	if (table->has_finished == table->heads)
	{
		pthread_mutex_unlock(&table->finished_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->finished_mutex);
	return (0);
}

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
		if (finished(table))
			break ;
		i++;
		if (i >= table->heads)
			i = 0;
	}
	return (NULL);
}

static void	ph_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->left]);
	if (!print_msg(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&table->forks[philo->left]);
		return ;
	}
	pthread_mutex_lock(&table->forks[philo->right]);
	if (!print_msg(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&table->forks[philo->left]);
		pthread_mutex_unlock(&table->forks[philo->right]);
		return ;
	}
	if (!print_msg(philo, "is eating"))
	{
		pthread_mutex_unlock(&table->forks[philo->right]);
		pthread_mutex_unlock(&table->forks[philo->left]);
		return ;
	}
	update_time(table, philo);
	my_sleep(table->time_to_eat);
	pthread_mutex_unlock(&table->forks[philo->right]);
	pthread_mutex_unlock(&table->forks[philo->left]);
}

void	*routine(t_philo *philo)
{
	t_table	*table;
	bool	i;
	bool	n;

	i = 0;
	n = (philo->index % 2 != 0 && philo->table->heads % 2 != 0);
	table = philo->table;
	pthread_mutex_lock(&philo->live_mutex);
	philo->time_to_live = get_time() + table->time_to_die;
	pthread_mutex_unlock(&philo->live_mutex);
	if (table->heads % 2 == 0)
		sleep_check(table, philo);
	while (1)
	{
		if (n && i)
			usleep(500);
		ph_eat(table, philo);
		if (!finish_check(table, philo))
			break ;
		print_msg(philo, "is sleeping");
		my_sleep(table->time_to_sleep);
		print_msg(philo, "is thinking");
		i = 1;
	}
	return (NULL);
}
