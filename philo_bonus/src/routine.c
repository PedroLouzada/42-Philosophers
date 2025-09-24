/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:39:18 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/24 20:03:56 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

void	*die(t_table *table)
{
	while (1)
	{
		if (!timer_check(table))
			break ;
		if (table->has_finished == table->heads)
		{
			table->is_over = 1;
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

static void	ph_eat(t_table *table)
{
	sem_wait(table->eaters);
	sem_wait(table->forks);
	if (!print_msg(table, "take a fork"))
	{
		sem_post(table->eaters);
		sem_post(table->forks);
		return ;
	}
	sem_wait(table->forks);
	if (!print_msg(table, "take a fork"))
	{
		sem_post(table->forks);
		sem_post(table->forks);
		sem_post(table->eaters);
		return ;
	}
	table->time_to_live += table->time_to_die;
	if (!print_msg(table, "is eating"))
	{
		sem_post(table->forks);
		sem_post(table->forks);
		sem_post(table->eaters);
		return ;
	}
	my_sleep(table->time_to_eat);
	sem_post(table->forks);
	sem_post(table->forks);
	sem_post(table->eaters);
}

void	routine(t_table *table)
{
	table->time_to_live = get_time() + table->time_to_die;
	while (1)
	{
		ph_eat(table);
		if (!print_msg(table, "is sleeping"))
			return ;
		if (table->is_over)
		{
			return ;
		}
		my_sleep(table->time_to_sleep);
	}
	return ;
}