/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:05:54 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/03 23:12:53 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void test_print(int ary[8])
{
	int idx = 0;
	ft_printf(" tmp->ary:");
	while(idx < 8)
	{
		ft_printf("%d", ary[idx]);
		idx++;
	}
	ft_printf(" ");
}
/*
	受け取ったバイトをchar*に変換して保持する
*/
int	set_to_str(t_pidlist *tmp)
{
	char	c;

	c = to_char(tmp->ary);
	// ft_printf("\n[set_to_str]%c,pid:%d\n", c[0], tmp->p_id); //test
	tmp->idx = 0;
	if (c == EOT)
	{
		tmp->recieved = 1;
		ft_printf("\n");
		return (1);
	}
	tmp->len++;
	ft_printf("%c", c);
	ft_printf("\n");//test
	// tmp->str = ft_strjoin(tmp->str, c);
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
