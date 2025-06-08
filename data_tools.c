/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:05:54 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/08 17:58:10 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	受け取ったバイトをchar*に変換して出力する
*/
int	print_char(t_data *tmp)
{
	char	c;

	c = to_char(tmp->ary);
	tmp->idx = 0;
	if (c == EOT)
	{
		ft_printf("\n");
		return (1);
	}
	ft_printf("%c", c);
	return (0);
}

/*
	PID構造体を初期化する
*/
void	clear_data(t_data *data)
{
	int		idx;

	data->p_id = 0;
	data->idx = 0;
	idx = 0;
	while (idx < 8)
		data->ary[idx++] = 0;
}
