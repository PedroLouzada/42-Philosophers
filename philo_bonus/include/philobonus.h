/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philobonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:55:04 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/24 20:04:22 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOBONUS_H
# define PHILOBONUS_H

# define MSG "Expected: Num_of_philo / Time_to_die /"
# define MSG2 " Time_to_eat / Time_to_sleep\n"
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_table
{
	int				heads;
	int				to_eat;
	int				my_pid;
	int				my_index;
	int				*child_pid;
	bool			optional;
	bool			is_over;
	void			*forks;
	void			*eaters;
	bool			has_finished;
	pthread_t		thread_id;
	size_t			time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_live;
}					t_table;

int					data_init(t_table *table, char **av);
int					char_check(char **av);
void				process_create(t_table *table);
long long int		ft_atol(const char *str);
void				routine(t_table *table);
unsigned long		get_time(void);
void				my_sleep(unsigned long time);
int					print_msg(t_table *table, char *msg);
void				time_passed(t_table *table);
void				*die(t_table *table);
int					timer_check(t_table *table);
#endif