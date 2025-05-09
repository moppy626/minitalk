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
	ハンドラ
*/
void	handler(int sig)
{
	static int ary[8];
	static int idx = 0;
	static int count = 0;

	// printf("signal: %d\n", sig);
	if (sig == SIGUSR1)
		ary[idx] = 1;
	else if (sig == SIGUSR2)
		ary[idx] = 0;
	idx++;
	if (idx >= 8)
	{
		ft_printf("%c", to_char(ary));
		idx = 0;
		count++;
	}
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	ft_printf("pid:%d\n", getpid());
	while(1)
		pause();
	return 0;
}
