/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/08 10:45:19 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_data;

/*
	PIDが登録されていなければ末尾に登録する
*/
void	add_pid(t_pidlist **list, int p_id)
{
	t_pidlist	*tmp;

	if (!*list)
	{
		*list = new_list(p_id);
		return ;
	}
	tmp = *list;
	while (tmp->next)
	{
		if (tmp->p_id == p_id)
			return ;
		tmp = tmp->next;
	}
	if (tmp->p_id == p_id)
		return ;
	tmp->next = new_list(p_id);
	return ;
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
	int			ret;

	g_data.pidlist = NULL;
	set_handler(handler);
	ft_printf("pid:%d\n", getpid());
	while (1)
	{
		ret = usleep(WAIT_TIME);
		// usleep(WAIT_TIME);
		// printf("ret:%d\n", ret);
		if (g_data.pidlist)
			printf("g_data.last_pid:%d,g_data.pidlist->p_id:%d\n",g_data.last_pid,g_data.pidlist->p_id);
		else
			printf("g_data.last_pid:%d\n",g_data.last_pid);
		if (g_data.last_pid)
		{
			if (g_data.pidlist && g_data.pidlist->p_id == g_data.last_pid)
			{
				// 処理
				if (ret == 0)
					write(1, "\n", 1);
					// error("Client has not replied\n", &g_data.pidlist);
				if (g_data.signal_flag == SIGUSR1)
				{
					// ft_printf("1"); //test
					g_data.pidlist->ary[g_data.pidlist->idx] = 1;
				}
				else if (g_data.signal_flag == SIGUSR2)
				{
					// ft_printf("0"); //test
					g_data.pidlist->ary[g_data.pidlist->idx] = 0;
				}
				g_data.pidlist->idx++;
				if (g_data.pidlist->idx >= 8 && print_char(g_data.pidlist))
				{
					// // ft_printf("%s\n", g_data.pidlist->str); //test
					kill(g_data.last_pid, g_data.signal_flag);
					g_data.pidlist = free_data(&g_data.pidlist);
					if (g_data.pidlist)
						kill(g_data.last_pid, g_data.signal_flag);
				}
				
			}
			else
				add_pid(&g_data.pidlist, g_data.last_pid);
			if (g_data.pidlist && g_data.pidlist->p_id == g_data.last_pid)
			{
				usleep(BLANK_MOMENT);
				printf("send:%d\n", g_data.signal_flag);
				kill(g_data.last_pid, g_data.signal_flag);
			}
			g_data.last_pid = 0;
		}
	}
	return (0);
}
