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
		printf("ary:%d, ret:%d\n", *ary, ret);
		class /= 2;
		ary++;
	}
	return (ret);
}
int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	int test[8] = {0, 1, 1, 0, 0, 0, 0, 1};
	char ret = to_char(test);
	printf("%c\n", ret);
	return 0;
}
