/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:50 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/24 21:49:54 by mmachida         ###   ########.fr       */
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

typedef struct s_data
{
	int				p_id;
	int				recieved;
	int				returned;
	int				ary[8];
	ssize_t			idx;
	char			*str;
	ssize_t			len;
	struct s_data	*next;
}	t_data;
int		set_to_str(t_data *tmp);
t_data	*new_data(int p_id);
void	free_data(t_data **data);
void	error(char *msg, t_data **data);
char	to_char(int *ary);
void	to_binary(char c, int *ary);
void	send_char(int p_id, char c);

#endif