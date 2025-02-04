/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozsipah < oozsipah@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:16:11 by oozsipah          #+#    #+#             */
/*   Updated: 2025/02/04 18:56:00 by oozsipah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

static void	collect_pid(pid_t *client_pid, int signal, int *pid_is_ready)
{
    static int	pid_bit;

    if (signal == SIGUSR1)
        *client_pid = (*client_pid << 1) | 1;
    else if (signal == SIGUSR2)
        *client_pid = *client_pid << 1;
    
    pid_bit++;
    if (pid_bit == 32)
    {
        *pid_is_ready = 1;
        pid_bit = 0;
    }
}

static void message_completed(int *pid_is_ready, pid_t *client_pid, int *bit_counter, char *ch)
{
    write(1, "\n", 1);
    kill(*client_pid, SIGUSR1);
    *pid_is_ready = 0;
    *bit_counter = 0;
    *ch = 0;
}

static void	handle_signal(int signal)
{
    static char     ch;
    static int      bit_counter;
    static pid_t    client_pid;
    static int      pid_is_ready;

    if (!pid_is_ready)
        collect_pid(&client_pid, signal, &pid_is_ready);
    else
    {
        if (signal == SIGUSR1)
            ch = (ch << 1) | 1;
        else if (signal == SIGUSR2)
            ch = ch << 1;
        bit_counter++;
        if (bit_counter == 8)
        {
            if (ch == '\0')
                message_completed(&pid_is_ready, &client_pid, &bit_counter, &ch);
            else
            {
                write(1, &ch, 1);
                kill (client_pid, SIGUSR2);
                bit_counter = 0;
                ch = 0;
            }
        }
    }
}

int	main(void)
{
    pid_t	server_pid;

    server_pid = getpid();
    printf("Server PID: %d\n", server_pid);

    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while (1)
        pause();
    
    return (0);
}