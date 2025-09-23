/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:02 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/23 16:22:05 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_check(t_table *table, t_philo *philo)
{
	if (table->optional && philo->has_eaten == table->to_eat)
	{
		pthread_mutex_lock(&table->finished_mutex);
		table->has_finished++;
		pthread_mutex_unlock(&table->finished_mutex);
		return (0);
	}
	pthread_mutex_lock(&table->over_mutex);
	if (table->over)
	{
		pthread_mutex_unlock(&table->over_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->over_mutex);
	return (1);
}

int	timer_check(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&philo->live_mutex);
	if (get_time() > philo->time_to_live)
	{
		pthread_mutex_unlock(&philo->live_mutex);
		print_msg(philo, "died");
		pthread_mutex_lock(&table->over_mutex);
		table->over = 1;
		pthread_mutex_unlock(&table->over_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->live_mutex);
	return (1);
}

void	time_passed(t_table *table)
{
	static unsigned long	last_time;
	static unsigned long	current_time;

	if (current_time == 0)
		last_time = get_time();
	current_time = get_time();
	table->time = current_time - last_time;
}

void	update_time(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&philo->live_mutex);
	philo->time_to_live = get_time() + table->time_to_die;
	pthread_mutex_unlock(&philo->live_mutex);
	philo->has_eaten++;
}

void	*one_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[0]);
	print_msg(philo, "take a fork");
	my_sleep(table->time_to_die + 1);
	print_msg(philo, "died");
	pthread_mutex_unlock(&table->forks[0]);
	return (NULL);
}
