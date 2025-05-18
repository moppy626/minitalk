/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/18 23:48:46 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	受信した値を送り返す
*/
void	send_recv_val(t_data *tmp)
{
	ssize_t			idx;

	idx = 0;
	while (tmp->str[idx])
		send_char(tmp->p_id, tmp->str[idx++]);
	send_char(tmp->p_id, EOT);
}

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static t_data	*tmp = NULL;

	(void)ucontext;
	if (sig == SIGINT)
	{
		free_data(&tmp);
		exit (0);
	}
	if (!tmp)
		tmp = new_data(info->si_pid);
	if (sig == SIGUSR1)
		tmp->ary[tmp->idx] = 1;
	else if (sig == SIGUSR2)
		tmp->ary[tmp->idx] = 0;
	tmp->idx++;
	if (tmp->idx >= 8 && set_to_str(tmp))
	{
		send_recv_val(tmp);
		free_data(&tmp);
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
		error("Failed in sigemptyset\n");
	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0
		|| sigaction(SIGINT, &sa, NULL) < 0)
		error("Failed in sigaction\n");
	ft_printf("pid:%d\n", getpid());
	while (1)
		pause();
	return (0);
}
