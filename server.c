/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/08 21:03:52 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_data;

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
	{
		exit (0);
	}
	g_data.signal_flag = sig;
	g_data.last_pid = info->si_pid;
}

/*

*/
void	recieve_data(t_data *data)
{
	if (!data->p_id)
		data->p_id = data->last_pid;
	else if (data->p_id == data->last_pid)
	{
		if (data->signal_flag == SIGUSR1)
			data->ary[data->idx] = 1;
		else if (data->signal_flag == SIGUSR2)
			data->ary[data->idx] = 0;
		data->idx++;
		if (data->idx >= 8 && print_char(data))
		{
			kill(data->p_id, data->signal_flag);
			clear_data(data);
		}
	}
	usleep(BLANK_MOMENT);
	kill(data->p_id, data->signal_flag);
}

/*
	serverメイン
*/
int	main(void)
{
	int		ret;

	set_handler(handler);
	clear_data(&g_data);
	ft_printf("pid:%d\n", getpid());
	while (1)
	{
		ret = usleep(WAIT_TIME * 10);
		if (g_data.p_id && ret == 0)
		{
			clear_data(&g_data);
			write(1, "\n", 1);
		}
		if (!g_data.last_pid)
			continue ;
		if (!g_data.p_id || g_data.p_id == g_data.last_pid)
			recieve_data(&g_data);
		g_data.last_pid = 0;
	}
	return (0);
}
