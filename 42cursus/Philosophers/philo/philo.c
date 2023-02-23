/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:00:03 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/23 23:53:40 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
args: Structure with the data of the philosopher
Return none.
Main function of the thread philosopher that starts
the routine.
*/
void	*philo_life(void *args)
{
	t_philo_memo	*memo;

	memo = (t_philo_memo *)args;
	pthread_mutex_lock(memo->start_flag);
	pthread_mutex_unlock(memo->start_flag);
	gettimeofday(&memo->last_eat, NULL);										//Set the start time
	usleep(1000);
	if (memo->philo_seat % 2 == 0)
		usleep(5000);															//So everyone doesn't take the left at the beginning
	while (*memo->semaph_end != 1)
	{
		if (*memo->semaph_end != 1)
		{
			pthread_mutex_lock(memo->print_prio);
			if (*memo->semaph_end != 1)
				printf("| %-14ld| %10d| %-24s|\n", get_timestamp(memo->time_start), memo->philo_seat, "is now thinking");
			pthread_mutex_unlock(memo->print_prio);
		}
		if (*memo->semaph_end != 1)
		{
			pthread_mutex_lock(memo->philo_fork_l);
			pthread_mutex_lock(memo->print_prio);
			if (*memo->semaph_end != 1)
				printf("| %-14ld| %10d| %-24s|\n", get_timestamp(memo->time_start), memo->philo_seat, "has taken the left fork");
			pthread_mutex_unlock(memo->print_prio);
		}
		if (*memo->semaph_end != 1)
		{
			pthread_mutex_lock(memo->philo_fork_r);
			pthread_mutex_lock(memo->print_prio);
			if (*memo->semaph_end != 1)
				printf("| %-14ld| %10d| %-24s|\n", get_timestamp(memo->time_start), memo->philo_seat, "has taken the right fork");
			gettimeofday(&memo->last_eat, NULL);								//Save eat time just before starting
			if (*memo->semaph_end != 1)
				printf("| %-14ld| %10d| %-24s|%d/%d\n", get_timestamp(memo->time_start), memo->philo_seat, "is now eating", memo->meals + 1, memo->philo_hungry);
			pthread_mutex_unlock(memo->print_prio);
		}
		if (*memo->semaph_end != 1)
		{
			usleep(memo->time_to_eat * 1000);
//			gettimeofday(&memo->last_eat, NULL);								//Save eat time as soon as finished (from subject we have to save only when philosopher start to eat)
			memo->meals++;
		}
		pthread_mutex_unlock(memo->philo_fork_r);
		pthread_mutex_unlock(memo->philo_fork_l);
		if (*memo->semaph_end != 1)
		{
			pthread_mutex_lock(memo->print_prio);
			if (*memo->semaph_end != 1)
				printf("| %-14ld| %10d| %-24s|\n", get_timestamp(memo->time_start), memo->philo_seat, "is now sleeping");
			pthread_mutex_unlock(memo->print_prio);
			if (*memo->semaph_end != 1)
				usleep(memo->time_to_sleep * 1000);
		}
	}
	return (0);
}
