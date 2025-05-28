/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/28 23:09:54 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	*g_data = NULL;

/*
	PIDを検索し、なければ末尾に追加する
*/
void	set_pid(t_data **data, int p_id)
{
	t_data	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (tmp->p_id == p_id)
			return ;
		tmp = tmp->next;
	}
	tmp = new_data(p_id);
}

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;


	if (sig == SIGINT)
	{
		free_list(&g_data);
		exit (0);
	}
	if (!g_data)
	{
		g_data = new_data(info->si_pid);
		return ;
	}
	printf("[handler]g_data->p_id:%d\n",g_data->p_id);
	if (g_data->p_id != info->si_pid)
		set_pid(&g_data, info->si_pid);
	else
	{
		if (sig == SIGUSR1)
		{
			ft_printf("1");
			g_data->ary[g_data->idx] = 1;
		}
		else if (sig == SIGUSR2)
		{
			ft_printf("0");
			g_data->ary[g_data->idx] = 0;
		}
		g_data->idx++;
		if (g_data->idx >= 8)
		{
			ft_printf("\n");
			if (set_to_str(g_data))
				g_data->recieved = 1;
		}
	}
}

/*
	serverメイン
*/
int	main(void)
{
	t_data	*temp;

	set_handler(handler);
	ft_printf("pid:%d\n", getpid());
	while (1)
	{
		while (!g_data)
			pause();
		kill(g_data->p_id, SIGUSR1);
		printf("send SIGUSR1 to %d\n", g_data->p_id);
		while (!g_data->recieved)
			pause();
		printf("recieved\n");
		ft_printf(g_data->str);
		kill(g_data->p_id, SIGUSR2);
		temp = g_data->next;
		free_data(&g_data);
		g_data = temp;
	}
	return (0);
}
