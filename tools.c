/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:46:49 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/11 16:46:49 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	エラーメッセージを出力して処理を終了する
*/
void	error(char *msg)
{
	int	len;

	len = ft_strlen(msg);
	write(2, "Error\n", 6);
	write(2, msg, len);
	exit (1);
}

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
	受け取ったバイトをchar*に変換して保持する
*/
void	set_to_str(t_data *tmp)
{
	char	c[2];

	c[0] = to_char(tmp->ary);
	c[1] = '\0';
	if (c[0] == EOT)
	{
		ft_printf("%s\n", tmp->str);
		return ;
	}
	tmp->len++;
	tmp->str = ft_strjoin(tmp->str, c);
	tmp->idx = 0;
}
