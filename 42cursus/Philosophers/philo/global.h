/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/09 16:20:07 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# define _POSIX_THREAD_SAFE_FUNCTIONS
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

enum e_bool {
	false,
	true,
};

enum e_io {
	in,
	out,
	err,
};

typedef struct s_philo_memo
{
	int				philo_seat;
	pthread_mutex_t	*philo_fork_r;
	pthread_mutex_t	*philo_fork_l;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				philo_hungry;
	int				*semaph_end;
	struct timeval	last_eat;
	struct timeval	time_start;
	pthread_mutex_t	*print_prio;
	pthread_mutex_t	*start_flag;
	pthread_mutex_t	*end_flag;
}	t_philo_memo;

typedef struct s_init
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_each;
	int				semaph_end;
	t_philo_memo	*table;
	struct timeval	time_start;
	pthread_mutex_t	print_prio;
	pthread_mutex_t	start_flag;
	pthread_mutex_t	end_flag;
}	t_init;

#endif
