/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozsipah < oozsipah@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:41:32 by oozsipah          #+#    #+#             */
/*   Updated: 2025/05/16 23:46:13 by oozsipah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdlib.h>
#include <unistd.h>

int			g_flag = 1;

static int wait_for_response(void)
{
    int timeout = 500000;
    
    while (timeout-- > 0)
    {
        if (g_flag == 0)
        {
            g_flag = 1;
            return 1;
        }
        usleep(1);
    }
    write(1, "Server doesn't respond\n", 23);
    return 0;
}

static void	send_pid(pid_t client_pid, pid_t server_pid)
{
	int	bit_counter;

	bit_counter = 31;
	while (bit_counter >= 0)
	{
		if ((client_pid >> bit_counter) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		bit_counter--;
	}
}

static void	handle_signal(int signal)
{
	if (signal == SIGUSR2)
		exit(0);
	else if (signal == SIGUSR1)
		g_flag = 0;
}

static void send_signal(const char *msg, pid_t server_pid)
{
    size_t i;
    size_t len;
    int bit_counter;
    
    i = 0;
    len = 0;
    while (msg[len++])
        ;
    while (i <= len)
    {
        bit_counter = 7;
        while (bit_counter >= 0)
        {
            if ((msg[i] >> bit_counter) & 1)
                kill(server_pid, SIGUSR1);
            else
                kill(server_pid, SIGUSR2);
            bit_counter--;
            if (!wait_for_response())
                exit(1);
        }
        i++;
    }
}

int	main(int ac, char **av)
{
	pid_t	client_pid;
	pid_t	server_pid;

	if (ac != 3)
	{
		write(1, "Usage: ./<program_name> <server_pid> <message>\n", 48);
		exit(1);
	}
	client_pid = getpid();
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0)
	{
		write(1, "Error: Invalid server PID\n", 27);
		exit(1);
	}
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	send_pid(client_pid, server_pid);
	send_signal(av[2], server_pid);
	send_signal("\n", server_pid);
	while (1)
		pause();
}
