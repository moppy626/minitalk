/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:30:09 by user42            #+#    #+#             */
/*   Updated: 2025/04/07 22:06:26 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c);

int	ft_atoi(const char *str)
{
	long	ret;
	int		i;
	int		fugou;

	i = 0;
	while (is_space((char)str[i]))
		i++;
	fugou = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			fugou = -1;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (ret > (LONG_MAX - (str[i] - '0')) / 10)
		{
			if (fugou == -1)
				return (0);
			else
				return ((int)LONG_MAX);
		}
		ret = (ret * 10) + (str[i++] - '0');
	}
	return (fugou * ret);
}

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}
