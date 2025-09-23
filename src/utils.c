/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:23:16 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/23 14:41:02 by pbongiov         ###   ########.fr       */
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

int	char_check(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!(str[i][j] >= '0' && str[i][j] <= '9'))
			{
				printf("Expected only nummeric arguments\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	my_sleep(unsigned long time)
{
	unsigned long	next_time;

	next_time = get_time() + time;
	while (get_time() < next_time)
		usleep(250);
}

int	print_msg(t_philo *philo, char *msg)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->time_mutex);
	time_passed(table);
	pthread_mutex_lock(&table->over_mutex);
	if (table->over)
	{
		pthread_mutex_unlock(&table->time_mutex);
		pthread_mutex_unlock(&table->over_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->over_mutex);
	printf("%ld %i %s\n", table->time, philo->index, msg);
	pthread_mutex_unlock(&table->time_mutex);
	return (1);
}
