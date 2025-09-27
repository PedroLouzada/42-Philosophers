/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:00:09 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/27 14:53:52 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

void	data_init(t_table *table, char **av)
{
	int	i;

	i = 1;
	if (!char_check(av))
		exit(1);
	while (av[i])
	{
		if (ft_atol(av[i++]) < 1)
			exit_error(1);
	}
	table->heads = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->time = 0;
	table->is_over = 0;
	table->optional = 0;
	table->has_died = 0;
	table->meal_count = 0;
	sem_start(table);
}

void	process_create(t_table *table)
{
	int	i;

	i = 0;
	table->child_pid = malloc(table->heads * sizeof(int));
	if (!table->child_pid)
		exit(0);
	time_passed(table);
	while (i < table->heads)
	{
		table->my_index = i + 1;
		table->my_pid = fork();
		if (table->my_pid == 0)
			break ;
		table->child_pid[i] = table->my_pid;
		i++;
	}
	if (table->my_pid != 0)
		return ;
	pthread_create(&table->die_id, NULL, (void *)die, table);
	pthread_detach(table->die_id);
	pthread_create(&table->alive_id, NULL, (void *)still_alive, table);
	pthread_detach(table->alive_id);
}

void	sem_start(t_table *table)
{
	sem_unlink("/done");
	table->done_sem = sem_open("/done", O_CREAT, 0666, 1);
	sem_unlink("/print");
	table->print_sem = sem_open("/print", O_CREAT, 0666, 1);
	if (table->print_sem == SEM_FAILED || table->done_sem == SEM_FAILED)
		exit_error(0);
	sem_unlink("/meal");
	table->meal_sem = sem_open("/meal", O_CREAT, 0666, 1);
	sem_unlink("/die");
	table->die_sem = sem_open("/die", O_CREAT, 0666, 0);
	if (table->die_sem == SEM_FAILED || table->meal_sem == SEM_FAILED)
		exit_error(0);
	sem_unlink("/forks");
	table->forks_sem = sem_open("/forks", O_CREAT, 0666, table->heads);
	sem_unlink("/eaters");
	table->eaters_sem = sem_open("/eaters", O_CREAT, 0666, table->heads / 2);
	if (table->eaters_sem == SEM_FAILED || table->forks_sem == SEM_FAILED)
		exit_error(0);
}
