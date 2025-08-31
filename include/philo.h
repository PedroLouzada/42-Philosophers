/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:55:04 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/31 20:02:55 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread_id;
	int					index;
	long long int		last_meal;
	t_table				*table;
}						t_philo;

struct					s_table
{
	int					heads;
	unsigned long		time;
	long long int		time_to_die;
	long long int		time_to_eat;
	long long int		time_to_sleep;
	pthread_t			die_id;
	pthread_mutex_t		*forks;
	t_philo				*philo;
};

long long int			ft_atol(const char *s);
void					*routine(t_philo *philo);
void					*die(t_table *table);
unsigned long			get_time(void);
void					data_init(t_table *table, char **av);
void					time_passed(t_table *table);

#endif