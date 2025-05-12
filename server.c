/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:25:01 by mmachida          #+#    #+#             */
/*   Updated: 2025/04/22 20:25:01 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	2進数の8ビット配列をcharに変換します
*/
char to_char(int *ary)
{
	int ret;
	int class;

	ret = 0;
	class = 128;
	while(class >= 1)
	{
		if (*ary)
			ret += class;
		class /= 2;
		ary++;
	}
	return (ret);
}
/*
	PIDから対応するデータを取得する
*/
t_data	*get_from_pid(t_data **data, int p_id)
{
	if (!*data)
	{
		*data = malloc(sizeof(t_data));
		(*data)->p_id = p_id;
		(*data)->idx = 0;
		(*data)->next = NULL;
		return (*data);
	}
	return (*data);
}

/*
	保持していたデータをfreeする
*/
void	free_data(t_data *data)
{
	free(data);
	data = NULL;
	exit(0);
}

/*
	ハンドラ
*/
void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	static t_data *data;
	t_data	*tmp;

	if (sig == SIGINT)
		free_data(data);

	tmp = get_from_pid(&data, info->si_pid);
	// printf("signal: %d\n", sig);
	if (sig == SIGUSR1)
	{
		tmp->ary[tmp->idx] = 1;
		// printf("1");
	}
	else if (sig == SIGUSR2)
	{
		tmp->ary[tmp->idx] = 0;
		// printf("0");
	}
	tmp->idx++;
	if (tmp->idx >= 8)
	{
		// printf("info->si_pid:%d\n",info->si_pid);
		char c = to_char(tmp->ary);
		if (c == EOT)
			ft_printf("\n");
		else
			ft_printf("%c", c);
		tmp->idx = 0;
	}
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	struct sigaction sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		return 1;
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	ft_printf("pid:%d\n", getpid());
	while(1)
		pause();
	return 0;
}
