/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:00:03 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/23 15:51:24 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static int	check_end(t_philo_memo philo, int *flag);

/*
set: Structure with all the data
Return none.
Main function of the thread daemon that checks
when philosophers are starved or have completed their meals.
*/
void	*demon_life(void *set)
{
	t_init	*table;
	int		i;
	int		flag;
	int		more_meals;

	flag = false;
	table = (t_init *)set;
	while (true)
	{
		usleep(3000);															//Delay before next check
		more_meals = 0;
		i = -1;
		while (++i < table->num_philo)
			more_meals += check_end(table->table[i], &flag);
		if (more_meals == table->num_philo)
		{
			pthread_mutex_lock(&table->end_flag);
			table->semaph_end = 1;
			pthread_mutex_unlock(&table->end_flag);
			pthread_mutex_lock(&table->print_prio);
			printf("------------------------------------------------------|Meals completed\n");
			pthread_mutex_unlock(&table->print_prio);
			break ;
		}
		if (flag != 0 && table->semaph_end == 0)
		{
			pthread_mutex_lock(&table->end_flag);
			table->semaph_end = 1;
			pthread_mutex_unlock(&table->end_flag);
			pthread_mutex_lock(&table->print_prio);
			printf("| %-14ld| %10d| %-24s|\n", get_timestamp(table->time_start), flag, "is died");
			printf("-------------------------------------------------------\n");
			pthread_mutex_unlock(&table->print_prio);
			break ;
		}
	}
	return (0);
}

/*
philo: Structure with all the data about the philosopher
flag: Reference to die flag variable
Return the state 1 if the philosopher ate all meals, 0 if not.
Check if all philosophers have eaten, and set the flag if someone died.
*/
static int	check_end(t_philo_memo philo, int *flag)
{
	if (get_timestamp(philo.last_eat) > philo.time_to_die)
		*flag = philo.philo_seat;
	if (philo.meals >= philo.philo_hungry && philo.philo_hungry != -1)
		return (1);
	return (0);
}
