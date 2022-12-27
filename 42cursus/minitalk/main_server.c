/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2022/12/27 16:13:36 by ecoli            ###   ########.fr       */
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
int	main(void)
{
	struct sigaction	act;
	pid_t				pid;

	pid = getpid();
	ft_memset(&act, '\0', sizeof(act));
	ft_putstr_fd("Process Identifier: ", out);
	ft_putnbr_fd((int)pid, out);
	ft_putchar_fd('\n', out);
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
	while (true)
		;										//Loop to keep the process alive and handle signals registered in the handler
	return (0);
}

/*
sig:Signal to handle.
siginfo: Build-in structure.
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
	static int	current_bit;
	static char	byte;

	if (sig == SIGUSR1)
	{
		byte &= ~(0x80 >> current_bit);			// 128 = 0x80 = 1000.0000
	}
	if (sig == SIGUSR2)
	{
		byte |= (128 >> current_bit);			// 128 = 0x80 = 1000.0000
	}
	current_bit++;
	if (current_bit == 8)						//Cause I use 8-bit char
	{
		if (byte == 0x10)						//Escape char DLE(Data Link Escape) 16 = 0x10 = 0001.0000
		{
			kill(siginfo->si_pid, SIGUSR2);		//Return signal for acknowledgment the client of escape Byte received
			ft_putchar_fd('\n', out);
		}
		ft_putchar_fd(byte, out);
		current_bit = 0;
		byte = 0;
		kill(siginfo->si_pid, SIGUSR1);			//Return signal for acknowledgment the client of Byte received
	}
}
