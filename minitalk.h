/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:50 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/06 00:11:28 by mmachida         ###   ########.fr       */
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
// # define WAIT_TIME	100000
# define WAIT_TIME	1000000
// # define BLANK_MOMENT	100
# define BLANK_MOMENT	100000
# define OUTPUT_TIME	1000

typedef struct s_pidlist
{
	int					p_id;
	int					receiving;
	int					recieved;
	int					ary[8];
	ssize_t				idx;
	// char				*str;
	ssize_t				len;
	struct s_pidlist	*next;
}	t_pidlist;

typedef struct s_data
{
	volatile		sig_atomic_t signal_flag;
	volatile		sig_atomic_t last_pid;
	struct s_pidlist	*pidlist;
}	t_data;
int			print_char(t_pidlist *tmp);
t_pidlist	*new_list(int p_id);
void		free_list(t_pidlist **data);
t_pidlist	*free_data(t_pidlist **data);
void		error(char *msg, t_pidlist **data);
char		to_char(int *ary);
void		to_binary(char c, int *ary);
void		set_handler(void (*handler)(int, siginfo_t *, void *));

#endif