/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:00:09 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/23 19:14:14 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

int	data_init(t_table *table, char **av)
{
    if (!char_check(av))
        return 2;
    table->heads = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->time = 0;
	table->optional = 0;
	if (table->heads < 1 || table->time_to_die < 1 || table->time_to_eat < 1 || table->time_to_sleep < 1)
		return (printf("Arguments must be greater than 0!\n"), 2);
    return 1;
}

void process_create(t_table *table)
{
    int i;
    
    i = 0;
    table->philo = malloc(table->heads * sizeof(t_philo));
    if (!table->philo)
        exit (0);
    while (i < table->heads)
    {
        table->philo[i].index = i + 1;
        table->philo[i].table = table;
        table->philo[i].pid = fork();
        if (table->philo[i].pid == 0)
            break;
        i++;
    }
}