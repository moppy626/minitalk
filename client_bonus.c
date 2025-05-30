/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:24:39 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/29 17:18:47 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int		g_sendflg = 0;

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;

	if (sig == SIGINT)
		exit(0);
	if (sig == SIGUSR1)
	{
		g_sendflg = 1;
		// printf("1\n");
	}
	else if (sig == SIGUSR2)
	{
		// printf("2\n");
		exit(0);
	}
}

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
	clientメイン
*/
int	main(int argc, char **argv)
{
	int					p_id;
	ssize_t				idx;

	printf("pid:%d\n", getpid());
	if (argc != 3)
		error("The parameter must be two\n", NULL);
	if (!is_only_number(argv[1]))
		error("PID must be number\n", NULL);
	p_id = ft_atoi(argv[1]);
	set_handler(handler);
	kill(p_id, SIGUSR1);
	while (!g_sendflg)
	{
		usleep(WAIT_TIME);
	}
	idx = 0;
	while (argv[2][idx] != '\0')
	{
		send_char(p_id, argv[2][idx++]);
		// printf("g_errflt:%d\n", g_errflg);
	}
	send_char(p_id, EOT);
	g_sendflg = 0;
	while(1)
		usleep(WAIT_TIME);
	return (0);
}
