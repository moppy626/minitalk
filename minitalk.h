/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:50 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/08 18:07:58 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

# include <stdio.h>

# define EOT		0x04
# define WAIT_TIME	100000
# define BLANK_MOMENT	100
# define OUTPUT_TIME	1000

typedef struct s_data
{
	volatile sig_atomic_t	signal_flag;
	volatile sig_atomic_t	last_pid;
	pid_t					p_id;
	int						ary[8];
	size_t					idx;
}	t_data;
int			print_char(t_data *tmp);
void		clear_data(t_data *list);
void		error(char *msg);
char		to_char(int *ary);
void		to_binary(char c, int *ary);
void		set_handler(void (*handler)(int, siginfo_t *, void *));

#endif