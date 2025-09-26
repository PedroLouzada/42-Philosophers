/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:39:18 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/26 19:25:15 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

void	*die(t_table *table)
{
	int i;

	i = 0;
	while (1)
	{
		sem_wait(table->meal_sem);
		if (get_time() > table->time_to_live)
		{
			print_msg(table, "died");
			while (i++ < table->heads)
				sem_post(table->die_sem);
			sem_post(table->meal_sem);
			exit(1);
		}
		sem_post(table->meal_sem);
		usleep(500);
	}
	return (NULL);
}
void	*still_alive(t_table *table)
{
	sem_wait(table->die_sem);
	exit(1);
	return (NULL);
}

void *finished(t_table *table)
{
	sem_wait(table->done_sem);
	exit(1);
	return (NULL);
}
static void	ph_eat(t_table *table)
{
	sem_wait(table->eaters_sem);
	sem_wait(table->forks_sem);
	print_msg(table, "take a fork");
	sem_wait(table->forks_sem);
	print_msg(table, "take a fork");
	sem_wait(table->meal_sem);
	table->time_to_live += table->time_to_die;
	sem_post(table->meal_sem);
	if (table->to_eat == ++table->meal_count)
		sem_post(table->done_sem);
	print_msg(table, "is eating");
	my_sleep(table->time_to_eat);
	sem_post(table->eaters_sem);
	sem_post(table->forks_sem);
	sem_post(table->forks_sem);
}

void	routine(t_table *table)
{
	table->time_to_live = get_time() + table->time_to_die;
	while (1)
	{
		ph_eat(table);
		print_msg(table, "is sleeping");
		my_sleep(table->time_to_sleep);
	}
	return ;
}