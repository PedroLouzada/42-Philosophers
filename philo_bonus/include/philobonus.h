/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philobonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:55:04 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/23 18:57:32 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOBONUS_H
# define PHILOBONUS_H

# define MSG "Expected: Num_of_philo / Time_to_die /"
# define MSG2 " Time_to_eat / Time_to_sleep\n"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					pid;
	int					index;
	int					has_eaten;
	unsigned long		time_to_live;
	t_table				*table;
}						t_philo;

struct					s_table
{
	int					heads;
	bool				optional;
	int					to_eat;
	unsigned long		time;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	t_philo				*philo;
};

int						data_init(t_table *table, char **av);
int						char_check(char **av);
void					process_create(t_table *table);
long long int			ft_atol(const char *str);
#endif