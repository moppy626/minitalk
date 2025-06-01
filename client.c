/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:24:39 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/01 23:14:11 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_data;

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
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
		exit (0);
	g_data.signal_flag = sig;
	g_data.last_pid = info->si_pid;
}

/*
	バイナリを送信する
*/
void	send_char(int p_id, char c)
{
	int	idx;
	int	ary[8];

	// printf("send:%c/", c);
	to_binary(c, ary);
	idx = 0;
	while (idx < 8)
	{
		pause();
		if (g_data.signal_flag == SIGUSR1
			&& g_data.last_pid == p_id)
		{
			usleep(WAIT_TIME);
			if (ary[idx])
			{
				printf("1");
				kill(p_id, SIGUSR1);
			}
			else
			{
				printf("0");
				kill(p_id, SIGUSR2);
			}
			idx++;
			g_data.signal_flag = 0;
		}
	}
	printf("\n");
}

/*
	clientメイン
*/
int	main(int argc, char **argv)
{
	int		p_id;
	ssize_t	idx;

	if (argc != 3)
		error("The parameter must be two\n", NULL);
	if (!is_only_number(argv[1]))
		error("PID must be number\n", NULL);
	set_handler(handler);
	p_id = ft_atoi(argv[1]);
	idx = 0;
	kill(p_id, SIGUSR1);
	while (argv[2][idx] != '\0')
	{
		send_char(p_id, argv[2][idx++]);
		printf("client roop\n");
	}
	send_char(p_id, EOT);
	return (0);
}
