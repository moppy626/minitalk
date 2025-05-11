/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:24:39 by mmachida          #+#    #+#             */
/*   Updated: 2025/04/22 20:24:39 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	与えられたchar文字を2進数に変換する
*/
void	to_binary(char c, int *ary)
{
	int	idx;
	unsigned msk;

	msk = 0x80;
	idx = 0;
	while (msk)
	{
		if (c & msk)
			ary[idx] = 1;
		else
			ary[idx] = 0;
		msk >>= 1;
		idx++;
	}
}
/*
	バイナリを送信する
*/
void	send_binary(int p_id, int *ary)
{
	int	idx;

	idx = 0;
	while (idx < 8)
	{
		if (ary[idx])
			kill(p_id, SIGUSR1);
		else
			kill(p_id, SIGUSR2);
		idx++;
		usleep(150);
	}
}

int main(int argc, char const **argv)
{
	(void) argc;
	int		ary[8];
	int		p_id;
	ssize_t	idx;

	p_id = ft_atoi(argv[1]);
	idx = 0;
	while (argv[2][idx] != '\0')
	{
		// printf("argv[2][idx]:%c\n", argv[2][idx]);
		to_binary(argv[2][idx], ary);
		send_binary(p_id, ary); 
		idx++;
	}
	return 0;
}

