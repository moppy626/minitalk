/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:05:54 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/01 16:48:40 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	受け取ったバイトをchar*に変換して保持する
*/
int	set_to_str(t_pidlist *tmp)
{
	char	c[2];

	c[0] = to_char(tmp->ary);
	c[1] = '\0';
	printf("\n[set_to_str]%c,pid:%d\n", c[0], tmp->p_id);
	tmp->idx = 0;
	if (c[0] == EOT)
	{
		tmp->recieved = 1;
		return (1);
	}
	tmp->len++;
	tmp->str = ft_strjoin(tmp->str, c);
	return (0);
}

/*
	新しいPID構造体を生成する
*/
t_pidlist	*new_list(int p_id)
{
	t_pidlist	*new;
	int		idx;

	new = malloc(sizeof(t_pidlist));
	new->p_id = p_id;
	new->idx = 0;
	new->recieved = 0;	
	new->next = NULL;
	new->str = NULL;
	new->len = 0;
	idx = 0;
	while (idx < 8)
		new->ary[idx++] = 0;
	return (new);
}
/*
	保持していたリストをfreeする
*/
void	free_list(t_pidlist **data)
{
	t_pidlist	*tmp;

	if (!*data)
		return ;
	tmp = *data;
	while (tmp)
	{
		*data = (*data)->next;
		tmp->p_id = 0;
		tmp->recieved = 0;
		tmp->idx = 0;
		free(tmp->str);
		tmp->len = 0;
		free(tmp);
		tmp = *data;
	}
	exit(0);
}

/*
	データをfreeする
*/
void	free_data(t_pidlist **data)
{
	if (!*data)
		return ;
	(*data)->p_id = 0;
	(*data)->recieved = 0;
	(*data)->idx = 0;
	free((*data)->str);
	(*data)->len = 0;
	free(*data);
}
