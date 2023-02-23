/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/02/23 23:30:14 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static int	set_param(t_init *set, char *argv[]);
static int	start_philos(t_init *set);

/*
*/
int	main(int argc, char *argv[])
{
	t_init	*rules;
	int		tmp;

	tmp = 0;
	if (argc != 5 && argc != 6)
		printf("Usage: %s number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
	else
	{
		rules = malloc(sizeof(t_init) * 1);
		if (!rules)
		{
			ft_putstr_fd("Malloc fail\n", err);
			return (1);
		}
		if (set_param(rules, argv) == 1)
		{
			free(rules);
			return (1);
		}
		pthread_mutex_init(&rules->print_prio, NULL);
		pthread_mutex_init(&rules->start_flag, NULL);
		pthread_mutex_init(&rules->end_flag, NULL);
		tmp = start_philos(rules);
		pthread_mutex_destroy(&rules->print_prio);
		pthread_mutex_destroy(&rules->start_flag);
		pthread_mutex_destroy(&rules->end_flag);
		free(rules);
	}
	return (tmp);
}

/*
set: Structure with all the data
Return the state 0 if all went well, 1 otherwise.
Initialize the philosopher structures, daemon
thread, and various mutexes. Then launch all
the various threads at once.
*/
static int	start_philos(t_init *set)
{
	pthread_t		id_philo[set->num_philo];
	pthread_t		id_demon;
	pthread_mutex_t	forks[set->num_philo];
	int				i;

	set->table = malloc(sizeof(t_philo_memo) * set->num_philo);
	if (!set->table)
	{
		ft_putstr_fd("Malloc fail\n", err);
		return (1);
	}
	i = -1;
	while (++i < set->num_philo)												//Loop to initialize philosophers
	{
		set->table[i].philo_seat = i + 1;
		set->table[i].philo_fork_r = &forks[(i + 1) % set->num_philo];			//Assigned the forks with the module
		set->table[i].philo_fork_l = &forks[(i) % set->num_philo];				//Assigned the forks with the module
		set->table[i].time_to_die = set->time_to_die;
		set->table[i].time_to_eat = set->time_to_eat;
		set->table[i].time_to_sleep = set->time_to_sleep;
		set->table[i].meals = 0;
		set->table[i].philo_hungry = set->meal_each;
		set->table[i].semaph_end = &set->semaph_end;							//Read-only to philosophers
		//set->table[i].last_eat = set->time_start								//Time is taken before creating the threads (specified later)
		//set->table[i].time_start = set->time_start							//Time is taken before creating the threads (specified later)
		set->table[i].print_prio = &set->print_prio;
		set->table[i].start_flag = &set->start_flag;
		set->table[i].end_flag = &set->end_flag;
	}
	i = -1;
	while (++i < set->num_philo)												//Loop to initialize mutex
		pthread_mutex_init(&forks[i], NULL);
	set->semaph_end = 0;
	pthread_mutex_lock(&set->start_flag);										//Take the mutex to prevent the immediate start of threads
	if (pthread_create(&id_demon, NULL, demon_life, (void *)set) != 0)			//To start demon
	{
		ft_putstr_fd("Pthread_create fail\n", err);
		i = -1;
		while (++i < set->num_philo)											//Loop to free mutex
			pthread_mutex_destroy(&forks[i]);
		pthread_mutex_lock(&set->end_flag);
		pthread_mutex_unlock(&set->start_flag);
		free(set->table);
		return (1);
	}
	if (gettimeofday(&set->time_start, NULL) != 0)								//Take the start time
	{
		ft_putstr_fd("Gettimeofday fail\n", err);
		free(set->table);
		return (1);
	}
	i = -1;
	while (++i < set->num_philo)												//Loop to start all philosophers
	{
		set->table[i].time_start = set->time_start;								//Related to the previous initialization
		set->table[i].last_eat = set->time_start;								//Related to the previous initialization
		if (pthread_create(&id_philo[i], NULL, philo_life, (void *)&set->table[i]) != 0)
		{
			ft_putstr_fd("Pthread_create fail\n", err);
			i = -1;																//Loop to free mutex
			while (++i < set->num_philo)
				pthread_mutex_destroy(&forks[i]);
			pthread_mutex_lock(&set->end_flag);
			pthread_mutex_unlock(&set->start_flag);
			free(set->table);
			return (1);
		}
	}
	printf("-------------------------------------------------------\n");
	printf("|%-15s|%-11s|%-25s|\n", "Time Stamp (ms)", "Philosopher", "Action");
	printf("-------------------------------------------------------\n");
	pthread_mutex_unlock(&set->start_flag);										//Release the lock to start all philosophers at the same time
	pthread_join(id_demon, NULL);
	if (set->num_philo == 1)
		pthread_detach(id_philo[0]);
	else {
		i = -1;
		while (++i < set->num_philo)											//Loop to join all threads
			pthread_join(id_philo[i], NULL);
	}
	i = -1;																		//Loop to free mutex
	while (++i < set->num_philo)
		pthread_mutex_destroy(&forks[i]);
	free(set->table);
	return (0);
}

/*
set: Structure with all the data
argv: Strings for parameter 
Return the state 0 if all went well, 1 otherwise.
Check the parameters to initialize
the global structure.
*/
static int	set_param(t_init *set, char *argv[])
{
	set->num_philo = adhoc_atoi(argv[1]);
	set->time_to_die = adhoc_atoi(argv[2]);
	set->time_to_eat = adhoc_atoi(argv[3]);
	set->time_to_sleep = adhoc_atoi(argv[4]);
	if (argv[5])
		set->meal_each = adhoc_atoi(argv[5]);
	else
		set->meal_each = -1;		//Unreachable parameter, equivalent to while true but for philosophers
	if (set->num_philo <= 0)
		printf("Philosophers must be at least 1. (Not '%s')\n", argv[1]);
	if (set->time_to_die <= 0)
		printf("Philosophers must survive at least for 1ms. (Not '%s')\n", argv[2]);
	if (set->time_to_eat <= 0)
		printf("Philosophers must eat at least for 1ms. (Not '%s')\n", argv[3]);
	if (set->time_to_sleep <= 0)
		printf("Philosophers must sleep at least for 1ms. (Not '%s')\n", argv[4]);
	if (argv[5] && set->meal_each <= 0)
		printf("Philosophers must eat at least 1 meal. (Not '%s')\n", argv[5]);
	if (!set->num_philo || !set->time_to_die || !set->time_to_eat || !set->time_to_sleep || !set->meal_each)
		return (1);
	return (0);
}
