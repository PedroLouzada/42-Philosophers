/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:03:04 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/24 20:04:11 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

int	char_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
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

void	my_sleep(unsigned long time)
{
	unsigned long	next_time;

	next_time = get_time() + time;
	while (get_time() < next_time)
		usleep(250);
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

int	print_msg(t_table *table, char *msg)
{
	time_passed(table);
	if (table->is_over)
	{
		return (0);
	}
	printf("%ld %i %s\n", table->time, table->my_index, msg);
	return (1);
}

int	timer_check(t_table *table)
{
	if (get_time() > table->time_to_live)
	{
		table->is_over = 1;
		print_msg(table, "died");
		return (0);
	}
	return (1);
}