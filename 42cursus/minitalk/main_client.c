/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2022/12/27 16:13:03 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static void	handler(int sig, siginfo_t *siginfo, void *context);

/*
WHERE:
struct sigaction {
	void (*sa_handler)(int);
	void (*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t sa_mask;
	int sa_flags;
	void (*sa_restorer)(void);
}
*/
int	main(int argc, char *argv[])
{
	struct sigaction	act;
	int					s_pid;
	int					current_bit;
	int					time_sleep;
	char				byte;

	time_sleep = 1000;
	if (argc != 3)
	{
		ft_putstr_fd("Usage: ", err);
		ft_putstr_fd(argv[0], err);
		ft_putstr_fd(" <server_pid> <message>\n", err);
		return (1);
	}
	if (ft_strlen(argv[2]) == 0)
	{
		ft_putstr_fd("Message needed\n", err);
		return (1);
	}
	ft_memset(&act, '\0', sizeof(act));
	s_pid = ft_atoi(argv[1]);
	act.sa_sigaction = &handler;				//Meaningful only when estabilishing a signal handler. More in 'man sigaction'
	act.sa_flags = SA_SIGINFO;					//When the SA_SIGINFO flag is specified in act.sa_flags, the signal handler address is passed via the act.sa_sigaction field. This handler takes three arguments. More in 'man sigaction'
	if (sigaction(SIGUSR1, &act, NULL) == -1)	//Examine and change a signal action
	{
		ft_putstr_fd("Sigaction(SIGUSR1) fail", err);
		return (1);
	}
	if (sigaction(SIGUSR2, &act, NULL) == -1)	//Examine and change a signal action
	{
		ft_putstr_fd("Sigaction(SIGUSR2) fail", err);
		return (1);
	}
	while (*argv[2])
	{
		current_bit = 8;
		byte = *argv[2]++;
		while (current_bit-- > 0)
		{
			if (byte >> current_bit & 0x01)		//Right shifted, then is bitwise AND operatio. 0x01 = 1 = 0000.0001
				kill(s_pid, SIGUSR2);			//Coded as send a 1
			else
				kill(s_pid, SIGUSR1);			//Coded as send a 0
			usleep(time_sleep);
		}
	}
	byte = 0x10;								//Escape byte 0x10 = 0001.0000
	current_bit = 8;
	while (current_bit-- > 0)
	{
		if (byte >> current_bit & 0x01)			//Right shifted, then is bitwise AND operation. 0x01 = 1 = 0000.0001
			kill(s_pid, SIGUSR2);				//Coded as send a 1
		else
			kill(s_pid, SIGUSR1);				//Coded as send a 0
		usleep(time_sleep);
	}
	
	while (true)
		;										//Loop to keep the process alive and handle signals registered in the handler
	return (0);
}

/*
sig: Signal to handle.
siginfo: Buinld-in structure.
context:
Manages the signals received by the process
WHERE:
typedef struct {
	int si_signo;
	int si_code;
	union sigval si_value;
	int si_errno;
	pid_t si_pid;
	uid_t si_uid;
	void *si_addr;
	int si_status;
	int si_band;
} siginfo_t;
*/
static void	handler(int sig, siginfo_t *siginfo, void *context)
{
	static int	received;

	if (sig == SIGUSR1)
	{
		received++;								//Count received bytes
	}
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("Received by Server(", out);
		ft_putnbr_fd(siginfo->si_pid, out);
		ft_putstr_fd(") - ", out);
		ft_putnbr_fd(received, out);
		ft_putstr_fd(" bytes\n", out);
		received = 0;							//Reset cunter for the next connection
		exit(0);
	}
}
