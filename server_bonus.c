/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozsipah < oozsipah@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:16:11 by oozsipah          #+#    #+#             */
/*   Updated: 2025/03/12 00:37:48 by oozsipah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>

static void	ft_putnbr(pid_t pid)
{
	if (pid > 9)
		ft_putnbr(pid / 10);
	write(1, &"0123456789"[pid % 10], 1);
}

static void	collect_pid(pid_t *client_pid, int signal, int *flag)
{
	if (signal == SIGUSR1)
		*client_pid = (*client_pid << 1) | 1;
	else if (signal == SIGUSR2)
		*client_pid = *client_pid << 1;
	*flag = *flag + 1;
}

static void	message_completed(int *flag, pid_t *client_pid, int *bit_counter,
		char *ch)
{
	kill(*client_pid, SIGUSR2);
	*flag = 0;
	*bit_counter = 0;
	*ch = 0;
	*client_pid = 0;
	write(1, "\n", 1);
}

static void	handle_signal(int signal)
{
	static t_msg_data	msg_data;

	if (msg_data.flag < 32)
		collect_pid(&msg_data.client_pid, signal, &msg_data.flag);
	else
	{
		if (signal == SIGUSR1)
			msg_data.ch = (msg_data.ch << 1) | 1;
		else if (signal == SIGUSR2)
			msg_data.ch = msg_data.ch << 1;
		if (++msg_data.bit_counter == 8)
		{
			write(1, &msg_data.ch, 1);
			if (msg_data.ch == '\0')
			{
				message_completed(&msg_data.flag, &msg_data.client_pid,
					&msg_data.bit_counter, &msg_data.ch);
				return ;
			}
			msg_data.bit_counter = 0;
			msg_data.ch = 0;
		}
		kill(msg_data.client_pid, SIGUSR1);
	}
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	write(1, "SERVER PID: ", 12);
	ft_putnbr(server_pid);
	write(1, "\n", 1);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
