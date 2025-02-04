/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozsipah < oozsipah@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:41:32 by oozsipah          #+#    #+#             */
/*   Updated: 2025/02/04 18:55:43 by oozsipah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int flag = 1;

static int	ft_atoi(const char *s)
{
    int	i;
    int	result;

    result = 0;
    i = 0;
    while ((s[i] == 32) || (s[i] >= 9 && s[i] <= 13))
        i++;
    while (s[i] >= '0' && s[i] <= '9')
    {
        result = (result * 10) + (s[i] - '0');
        i++;
    }
    return (result);
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
    if (signal == SIGUSR1)
        write(1, "Server: Message recived.", 24);
    else if (signal == SIGUSR2)
        flag = 1;
}

static void	send_signal(const char *msg, pid_t server_pid)
{
    size_t	i;
    int		bit_counter;

    if (!msg)
        return;
    i = 0;
    while (msg[i])
    {
        bit_counter = 7;
        while (bit_counter >= 0)
        {
            if (flag)
            {
                if ((msg[i] >> bit_counter) & 1)
                    kill(server_pid, SIGUSR1);
                else
                    kill(server_pid, SIGUSR2);
                if (flag)
                    flag = 0;
                bit_counter--;
            }
        }
        i++;
    }
    bit_counter = 7;
    while (bit_counter >= 0)
    {
        kill(server_pid, SIGUSR2);
        bit_counter--;
        if (flag)
            flag = 0;
    }
}

int	main(int ac, char **av)
{
    pid_t	client_pid;
    pid_t	server_pid;

    if (ac != 3)
    {
        printf("Usage: %s <server_pid> <message>\n", av[0]);
        return (1);
    }
    client_pid = getpid();
    server_pid = ft_atoi(av[1]);
    if (server_pid < 0)
    {
        printf("Error: Invalid server PID\n");
        return (1);
    }
    printf("Client PID: %d\n", client_pid);
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
    send_pid(client_pid, server_pid);
    send_signal(av[2], server_pid);
    while (1)
        pause();
    return (0);
}