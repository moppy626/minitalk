/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:05:54 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/20 22:59:19 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	受け取ったバイトをchar*に変換して保持する
*/
int	set_to_str(t_data *tmp)
{
	char	c[2];

	c[0] = to_char(tmp->ary);
	c[1] = '\0';
	printf("%c", c[0]);
	tmp->idx = 0;
	if (c[0] == EOT)
	{
		printf("\n");
		ft_printf("%s\n", tmp->str);
		tmp->len = 0;
		return (1);
	}
	if (c[0] == NAK)
	{
		error("Another client is sending\n");
		free_data(&tmp);
	}
	tmp->len++;
	tmp->str = ft_strjoin(tmp->str, c);
	return (0);
}

/*
	新しいPID構造体を生成する
*/
t_data	*new_data(int p_id)
{
	t_data	*new;
	int		idx;

	new = malloc(sizeof(t_data));
	new->p_id = p_id;
	new->idx = 0;
	new->str = NULL;
	new->len = 0;
	idx = 0;
	while (idx < 8)
		new->ary[idx++] = 0;
	return (new);
}

/*
	保持していたデータをfreeする
*/
void	free_data(t_data **tmp)
{
	if (!*tmp)
		return ;
	free((*tmp)->str);
	free(*tmp);
	*tmp = NULL;
}
