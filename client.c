/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:24:39 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/08 00:21:57 by mmachida         ###   ########.fr       */
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
	int ret;
	int send;
	int	ary[8];

	ft_printf("send:%c/", c); //test
	to_binary(c, ary);
	idx = 0;
	while (idx < 8)
	{
		if (ary[idx])
		{
			ft_printf("1"); //test
			send = SIGUSR1;
		}
		else
		{
			ft_printf("0"); //test
			send = SIGUSR2;
		}
		kill(p_id, send);
		idx++;
		g_data.signal_flag = 0;
		ret = usleep(WAIT_TIME);
		// ft_printf("ret:%d\n", ret);//test
		if(ret == 0)
			idx--;
		else if (g_data.signal_flag != send)
			error("Failed to send\n", NULL);
		usleep(BLANK_MOMENT);

	}
	usleep(OUTPUT_TIME);
	ft_printf("\n"); //test
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
	printf("pid:%d\n", getpid()); //test
	set_handler(handler);
	p_id = ft_atoi(argv[1]);
	idx = 0;
	kill(p_id, SIGUSR1);
	pause();
	while (argv[2][idx] != '\0')
	{
		send_char(p_id, argv[2][idx++]);
	}
	send_char(p_id, EOT);
	return (0);
}
