/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/04 22:43:19 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_data;

/*
	PIDから対応するデータを取得する
*/
t_pidlist	*get_from_pid(t_pidlist **list, int p_id)
{
	t_pidlist	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->p_id == p_id)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = new_list(p_id);
	tmp->next = *list;
	*list = tmp;
	return (NULL);
}

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
	{
		free_list(&g_data.pidlist);
		exit (0);
	}
	g_data.signal_flag = sig;
	g_data.last_pid = info->si_pid;
}

/*
	serverメイン
*/
int	main(void)
{
	t_pidlist	*tmp;
	int			ret;

	set_handler(handler);
	ft_printf("pid:%d\n", getpid());
	while (1)
	{
		ret = usleep(WAIT_TIME);
		// printf("ret:%d\n", ret);
		if (g_data.last_pid)
		{
			tmp = get_from_pid(&g_data.pidlist, g_data.last_pid);
			if (tmp)
			{
				if (ret == 0)
					error("Client has not replied\n", &g_data.pidlist);
				if (g_data.signal_flag == SIGUSR1)
				{
					// ft_printf("1"); //test
					tmp->ary[tmp->idx] = 1;
				}
				else if (g_data.signal_flag == SIGUSR2)
				{
					// ft_printf("0"); //test
					tmp->ary[tmp->idx] = 0;
				}
				tmp->idx++;
				if (tmp->idx >= 8 && set_to_str(tmp))
				{
					// ft_printf("%s\n", tmp->str); //test
					g_data.pidlist = free_data(&g_data.pidlist);
				}
				
			}
			usleep(BLANK_MOMENT);
			kill(g_data.last_pid, g_data.signal_flag);
			g_data.last_pid = 0;
		}
	}
	return (0);
}