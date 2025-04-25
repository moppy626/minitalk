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

void	signal_handler(int sig)
{
	printf("catch: %d\n", sig);
}
int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	signal(SIGUSR1, signal_handler);
	while (1)
		pause();
	
	return 0;
}
