/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/21 23:49:42 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	PIDから対応するデータを取得する
*/
t_data	*get_from_pid(t_data **data, int p_id)
{
	t_data	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (tmp->p_id == p_id)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = new_data(p_id);
	tmp->next = *data;
	*data = tmp;
	return (*data);
}

/*
	受信した値を送り返す
*/
void	send_recv_val(t_data **data)
{
	t_data	*tmp;
	ssize_t	idx;

	tmp = *data;
	while (tmp)
	{
		printf("[send_recv_val]str:%s,returned:%d\n",tmp->str,tmp->returned);
		if (!tmp->returned)
		{
			idx = 0;
			while (tmp->str[idx])
				send_char(tmp->p_id, tmp->str[idx++]);
			send_char(tmp->p_id, EOT);
			tmp->returned = 1;
		}
		tmp = tmp->next;
	}
}

/*
	すべてのプロセスを受け取り済みか確認
*/
int	is_all_recieved(t_data	*data)
{
	t_data	*tmp;
	int		cnt;

	cnt = 0;
	tmp = data;
	while (tmp)
	{
		cnt++;
		if (!tmp->recieved)
		{
			printf("[is_all_recieved]not recieved%d\n", cnt);
			return (0);
		}
		tmp = tmp->next;
	}
	printf("[is_all_recieved]recieved%d\n", cnt);
	return (1);
}

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static t_data	*data = NULL;
	static int		sending = 0;
	t_data			*tmp;

	(void)ucontext;
	if (sig == SIGINT)
		free_data(&data);
	if (sending)
		send_char(info->si_pid, NAK);
	tmp = get_from_pid(&data, info->si_pid);
	if (sig == SIGUSR1)
	{
		printf("1");
		tmp->ary[tmp->idx] = 1;
	}
	else if (sig == SIGUSR2)
	{
		printf("0");
		tmp->ary[tmp->idx] = 0;
	}
	tmp->idx++;
	if (tmp->idx >= 8)
		if (set_to_str(tmp) && is_all_recieved(data))
		{
			sending = 1;
			send_recv_val(&data);
			sending = 0;
		}
}

/*
	serverメイン
*/
int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) < 0)
		error("Failed in sigemptyset\n", NULL);
	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0
		|| sigaction(SIGINT, &sa, NULL) < 0)
		error("Failed in sigaction\n", NULL);
	ft_printf("pid:%d\n", getpid());
	while (1)
		pause();
	return (0);
}
