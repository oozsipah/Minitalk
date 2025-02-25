/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozsipah <oozsipah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:16:11 by oozsipah          #+#    #+#             */
/*   Updated: 2025/02/25 20:44:32 by oozsipah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// static void	collect_pid(__pid_t *client_pid, int signal, int *pid_is_ready)
// {
//     static int	pid_bit;


//     if (signal == SIGUSR1)
//         *client_pid = (*client_pid << 1) & 1;
//     else if (signal == SIGUSR2)
//         *client_pid = *client_pid << 1;
    
//     pid_bit++;
//     if (pid_bit == 32)
//     {
//         *pid_is_ready = 1;
//         pid_bit = 0;
//     }
// }

static void message_completed(int *flag, __pid_t *client_pid, int *bit_counter, char *ch)
{
    kill(*client_pid, SIGUSR1);
    *flag = 0;
    *bit_counter = 0;
    *ch = 0;
    *client_pid = 0;
}

static void	handle_signal(int signal)
{
    static char     ch = 0;
    static int      i  = 0;
    static int      bit_counter = 0;
    static __pid_t    client_pid = 0;
    static int      flag = 0;
    
    //step 1;
    if (flag < 32)
    {
        if (signal == SIGUSR1)
            client_pid = (client_pid << 1) | 1;
        else if (signal == SIGUSR2)
            client_pid = client_pid << 1;
        flag++;
    }
    else
    {
        if (signal == SIGUSR1)
            ch = (ch << 1) | 1;
        else if (signal == SIGUSR2)
            ch = ch << 1;
        if (++bit_counter == 8)
        {
            write(1, &ch, 1);
            if (ch == '\0')
                message_completed(&flag, &client_pid, &bit_counter, &ch);
            bit_counter = 0;
            ch = 0;
        }
        kill (client_pid, SIGUSR2);
    }
    printf("Client Pid -> : %d | Bit Counter -> : %d\n", client_pid,i);
    i++;
}

int	main(void)
{
    __pid_t	server_pid;

    server_pid = getpid();
    printf("Server PID: %d\n", server_pid);

    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while (1)
        pause();
    
    return (0);
}