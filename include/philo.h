/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:55:04 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/18 17:48:48 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MSG "Expected: Num_of_philo / Time_to_die / Time_to_eat / Time_to_sleep\n"

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
	int					has_eaten;
	unsigned long		time_to_live;
	int					left;
	int					right;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		live_mutex;
	t_table				*table;
}						t_philo;

struct					s_table
{
	bool				over;
	int					heads;
	int					has_finished;
	bool				optional;
	int					to_eat;
	unsigned long		time;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	pthread_t			die_id;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		over_mutex;
	pthread_mutex_t		finished_mutex;
	pthread_mutex_t		*forks;
	t_philo				*philo;
};

long long int			ft_atol(const char *s);
void					*routine(t_philo *philo);
void					*die(t_table *table);
unsigned long			get_time(void);
int						data_init(t_table *table, char **av);
void					time_passed(t_table *table);
void					my_sleep(unsigned long time);
int						print_msg(t_philo *philo, char *msg);
void					free_stuff(t_table *table);
void					thread_create(t_table *table);
#endif