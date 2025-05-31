/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/31 23:18:21 by mmachida         ###   ########.fr       */
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
	return (*list);
}

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
		free_list(&g_data.pidlist);
	g_data.signal_flag = sig;
	g_data.last_pid = info->si_pid;
}

/*
	serverメイン
*/
int	main(void)
{
	t_pidlist			*tmp;

	set_handler(handler);
	ft_printf("pid:%d\n", getpid());
	while (1)
	{
		pause();
		tmp = get_from_pid(&g_data.pidlist, g_data.last_pid);
		if (g_data.signal_flag == SIGUSR1)
		{
			// printf("1");
			tmp->ary[tmp->idx] = 1;
		}
		else if (g_data.signal_flag == SIGUSR2)
		{
			// printf("0");
			tmp->ary[tmp->idx] = 0;
		}
		tmp->idx++;
		if (tmp->idx >= 8)
			if(set_to_str(tmp))
				ft_printf("%s\n", tmp->str);
	}
	return (0);
}
