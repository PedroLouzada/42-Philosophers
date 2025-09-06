/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:23:16 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/07 00:43:17 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_atol(const char *str)
{
	int				i;
	int				sign;
	long long int	n;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	time_passed(t_table *table)
{
	static unsigned long last_time;
	static unsigned long current_time;

	if (current_time == 0)
		last_time = get_time();
	current_time = get_time();
	table->time = current_time - last_time;
}

void	my_sleep(unsigned long time)
{
	unsigned long next_time;

	next_time = get_time() + time;
	while (get_time() < next_time)
		usleep(250);
}

void print_msg(t_philo *philo, char *msg)
{
	t_table *table;

	table = philo->table;
	time_passed(table);
	printf("%ld %i %s\n", table->time, philo->index, msg);
}