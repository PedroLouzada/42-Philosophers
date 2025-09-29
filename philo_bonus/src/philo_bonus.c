/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:35:44 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/29 19:34:24 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

int	main(int ac, char **av)
{
	int		i;
	t_table	table;

	if (ac < 5 || ac > 6)
		return (printf(MSG MSG2), 0);
	data_init(&table, av);
	if (ac == 6)
	{
		table.optional = 1;
		table.to_eat = ft_atol(av[5]);
	}
	else
		table.to_eat = 0;
	process_create(&table);
	if (table.my_pid == 0)
		routine(&table);
	i = 0;
	while (i < table.heads)
	{
		waitpid(table.child_pid[i], NULL, 0);
		i++;
	}
	unlink_stuff(&table);
}
