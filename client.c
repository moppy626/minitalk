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
	int	msk;

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
void	send_char(int p_id, char c)
{
	int	idx;
	int	ary[8];

	to_binary(c, ary);
	idx = 0;
	while (idx < 8)
	{
		if (ary[idx])
			kill(p_id, SIGUSR1);
		else
			kill(p_id, SIGUSR2);
		idx++;
		usleep(WAIT_TIME);
	}
}

/*
	clientメイン
*/
int	main(int argc, char **argv)
{
	int		p_id;
	ssize_t	idx;

	if (argc != 3)
		error("The parameter must be two\n");
	if (!is_only_number(argv[1]))
		error("PID must be number\n");
	p_id = ft_atoi(argv[1]);
	idx = 0;
	while (argv[2][idx] != '\0')
		send_char(p_id, argv[2][idx++]);
	send_char(p_id, EOT);
	return (0);
}
