/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozsipah <oozsipah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:45:06 by oozsipah          #+#    #+#             */
/*   Updated: 2025/02/25 12:36:27 by oozsipah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

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

void    send_msg(__pid_t  server_pid, char *msg)
{
    int bit_counter;
    int i;

    i = 0;
    while (msg[i])
    {
        bit_counter = 7;
        while (bit_counter >= 0)
        {
            if ((msg[i] >> bit_counter) & 1)
                kill(server_pid, SIGUSR1);
            else
                kill(server_pid, SIGUSR2);
            bit_counter--;
            usleep(100);
        }
        i++;
    }
    bit_counter = 7;
    while (bit_counter >= 0)
    {
        kill(server_pid, SIGUSR2);
        bit_counter--;
        usleep(100);
    }
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        write(1, "Usage: name of program <server_pid> <message>\n", 46);
        return (1);
    }
    __pid_t server_pid = ft_atoi(av[1]);
    if (server_pid < 0)
        write(1, "server pid cannot be negative!", 30);
    send_msg(server_pid, av[2]);
    return (0);
}
