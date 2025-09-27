/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:03:04 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/27 17:17:32 by pbongiov         ###   ########.fr       */
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
	sem_wait(table->print_sem);
	printf("%ld %i %s\n", table->time, table->my_index, msg);
	sem_post(table->print_sem);
	return (1);
}

void exit_error(int i)
{
	if (i == 0)
		printf("Error on semaphore creation\n");
	else if (i == 1)
		printf("Arguments must be greater than 0\n");
	exit (1);
}
static int	num_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	num;

	len = num_len(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '/';
	str[len] = '\0';
	num = n;
	while (num > 0)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}
