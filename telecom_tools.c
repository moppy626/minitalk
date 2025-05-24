/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   telecom_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:46:49 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/24 20:49:34 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	エラーメッセージを出力して処理を終了する
*/
void	error(char *msg, t_data **data)
{
	int	len;

	if (*data)
		free_data(data);
	len = ft_strlen(msg);
	write(2, "Error\n", 6);
	write(2, msg, len);
	exit (1);
}

/*
	2進数の8ビット配列をcharに変換します
*/
char	to_char(int *ary)
{
	int	ret;
	int	class;

	ret = 0;
	class = 128;
	while (class >= 1)
	{
		if (*ary)
			ret += class;
		class /= 2;
		ary++;
	}
	return (ret);
}

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
		printf("%d", ary[idx]);
		idx++;
	}
	printf("\n");
}

/*
	バイナリを送信する
*/
void	send_char(int p_id, char c)
{
	int	idx;
	int	ary[8];

	printf("send:%c/", c);
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
