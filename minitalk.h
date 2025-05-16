/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozsipah <oozsipah@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:56:29 by oozsipah          #+#    #+#             */
/*   Updated: 2025/03/12 17:10:25 by oozsipah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>

typedef struct s_msg_data
{
	char	ch;
	int		bit_counter;
	pid_t	client_pid;
	int		flag;
}			t_msg_data;

int ft_atoi(const char *s);

#endif