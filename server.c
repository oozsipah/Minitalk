/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozsipah < oozsipah@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:44:57 by oozsipah          #+#    #+#             */
/*   Updated: 2025/02/09 18:45:36 by oozsipah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void ft_putnbr(pid_t num)
{
    if (num > 9)
        ft_putnbr(num / 10);
    write(1, &"0123456789"[num % 10], 1);
}

void    signal_handler(int signal)
{
    static char ch;
    static int bit_counter;
    
    if (signal == SIGUSR1)
        ch = (ch << 1) | 1;
    else
        ch = ch << 1;
    bit_counter++;

    if (bit_counter == 8)
    {
        if (ch == '\0')
            write(1, "\nmessage recivied\n", 18);
        write(1, &ch, 1);
        ch = 0;
        bit_counter = 0;
    }
}

int main(void)
{
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    pid_t server_pid = getpid();
    ft_putnbr(server_pid);
    write(1, "\n", 1);
    while (1)
        pause();
    return(1);
}