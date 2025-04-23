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

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	ssize_t	idx;
	int test[8];

	idx = 0;
	printf("数字型へ");
	printf("%d", argv[1][idx]);
	to_binary(argv[1][idx], test);

	printf("\n");
	printf("変換後");
	idx = 0;
	while (idx < 8)
	{
		printf("%d", test[idx]);
		idx++;
	}
	printf("\n");
	
	return 0;
}

