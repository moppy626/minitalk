/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/28 23:10:28 by mmachida         ###   ########.fr       */
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
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static t_data	*data = NULL;
	t_data			*tmp;

	(void)ucontext;
	if (sig == SIGINT)
		free_list(&data);
	tmp = get_from_pid(&data, info->si_pid);
	if (sig == SIGUSR1)
		tmp->ary[tmp->idx] = 1;
	else if (sig == SIGUSR2)
		tmp->ary[tmp->idx] = 0;
	tmp->idx++;
	if (tmp->idx >= 8)
		set_to_str(tmp);
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
