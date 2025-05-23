/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:24:39 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/21 23:36:43 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_str;

/*
	パラメタが数字のみであることを確認する
*/
int	is_only_number(char *param)
{
	while (*param != '\0')
	{
		if (!ft_isdigit(*param))
			return (0);
		param++;
	}
	return (1);
}

/*
	戻り値を検証する
*/
void	check_retval(t_data	**tmp)
{
	ssize_t			idx;

	idx = 0;
	while (idx < (*tmp)->len)
	{
		if ((*tmp)->str[idx] != g_str[idx])
			error("Failed to send\n", tmp);
		idx++;
	}
}

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static t_data	*tmp = NULL;

	(void)ucontext;
	if (sig == SIGINT)
		free_data(&tmp);
	if (!tmp)
		tmp = new_data(info->si_pid);
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
	if (tmp->idx >= 8 && set_to_str(tmp))
	{
		check_retval(&tmp);
		free_data(&tmp);
	}
}

/*
	clientメイン
*/
int	main(int argc, char **argv)
{
	int					p_id;
	ssize_t				idx;
	struct sigaction	sa;

	if (argc != 3)
		error("The parameter must be two\n", NULL);
	if (!is_only_number(argv[1]))
		error("PID must be number\n", NULL);
	p_id = ft_atoi(argv[1]);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	g_str = argv[2];
	if (sigemptyset(&sa.sa_mask) < 0)
		error("Failed in sigemptyset\n", NULL);
	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0
		|| sigaction(SIGINT, &sa, NULL) < 0)
		error("Failed in sigaction\n", NULL);
	idx = 0;
	while (argv[2][idx] != '\0')
		send_char(p_id, argv[2][idx++]);
	send_char(p_id, EOT);
	while (1)
		pause();
	return (0);
}
