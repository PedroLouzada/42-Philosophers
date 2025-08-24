/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socrates.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:46:00 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/24 18:29:53 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	static int i;

	i = 0;
	printf("arg: %d\n", philo->index);
	//sleep(5);
	return NULL;
}

int main(int ac, char **av)
{
	static t_table table;
	int i;
	int n;
	
	if (ac < 4 || ac > 5)
		return (0);
	i = 0;
	n = ft_atoi(av[1]);
	table.philo = malloc(sizeof(t_philo) * (n + 1));
	while (i < n)
	{
		table.philo[i].table = &table;
		table.philo[i].index = i;
		pthread_create(&table.philo[i].thread_id, NULL, (void *)routine, &table.philo[i]);
		i++;
	}
	i = 0;
	while (i < n)
		pthread_join(table.philo[i++].thread_id, NULL);
	free(table.philo);
	//sleep(10);
}