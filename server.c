/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 01:06:24 by zcherrad          #+#    #+#             */
/*   Updated: 2022/03/13 01:47:17 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    _init()
{
	ft_bzero(&g_mini.buffer, sizeof(g_mini.buffer));
g_mini.top_byte = 0;
g_mini.top_bit = 1 << 7; // 128
g_mini.all_done = 0;
}

void    main_server()
{
	pid_t    pid;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	_init();
	while (1)
	{
		if (g_mini.all_done == 1)
		{
			ft_putendl_fd(g_mini.buffer, 1);
			_init();
		}
		pause();
	}
}

void    true_bit_handler(int signo, siginfo_t *info, void *context)
{
	(void)signo;
	(void)context;
	(void)info;
	if (g_mini.top_bit == 0)
	{
		g_mini.top_bit = 1 << 7;
		g_mini.top_byte += 1;
	}
	g_mini.buffer[g_mini.top_byte] |= g_mini.top_bit;
	g_mini.top_bit >>= 1;
}

void    false_bit_handler(int signo, siginfo_t *info, void *context)
{
	(void)signo;
	(void)context;
	if (g_mini.top_bit == 0)
	{
		g_mini.top_bit = 1 << 7;
		g_mini.top_byte += 1;
	}
	g_mini.top_bit >>= 1;
	if (g_mini.top_bit == 0 && g_mini.buffer[g_mini.top_byte] == '\0')
	{
		g_mini.all_done = 1;
		kill(info->si_pid, SIGUSR1);
	}
}

int main(void)
{
	struct sigaction true_bit; // when the server receive SIGUSR1 
	struct sigaction false_bit; // when the server receive SIGUSR2 
	
	//activation of sa_sigaction with SA_SIGINFO
	true_bit.sa_flags = SA_SIGINFO;
	false_bit.sa_flags = SA_SIGINFO;

	true_bit.sa_sigaction = &true_bit_handler;
	false_bit.sa_sigaction = &false_bit_handler;
	if (sigaction(SIGUSR1, &true_bit, NULL) == -1)
	{
		ft_putstr_fd("error", 2);
		exit(1);
	}
	if (sigaction(SIGUSR2, &false_bit, NULL) == -1)
	{
		ft_putstr_fd("error", 2);
		exit(1);
	}
	main_server();
	return (0);
}