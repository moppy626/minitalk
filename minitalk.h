/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:50 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/15 22:26:50 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

# define EOT		0x04
# define WAIT_TIME	10000

typedef struct s_data{
	int				p_id;
	int				ary[8];
	ssize_t			idx;
	char			*str;
	ssize_t			len;
	struct s_data	*next;
}	t_data;
void	error(char *msg);
int		is_only_number(char *param);
char	to_char(int *ary);
void	set_to_str(t_data	*tmp);

#endif