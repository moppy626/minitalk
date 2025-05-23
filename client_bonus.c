/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:24:39 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/24 21:41:56 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
	{
		printf("1");
		exit(0);
	}
	else if (sig == SIGUSR2)
	{
		printf("0");
		error("Failed to send\n", NULL);
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
	return (0);
}
