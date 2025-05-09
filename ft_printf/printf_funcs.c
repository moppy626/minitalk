/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:24:28 by user42            #+#    #+#             */
/*   Updated: 2024/08/14 17:36:22 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	set_int(char *dest, int param)
{
	long	idx;

	if (param == -2147483648)
	{
		if (dest != NULL)
			ft_memcpy(dest, "-2147483648", 11);
		return (11);
	}

	if (param < 0)
	{
		if (dest != NULL)
			dest[0] = '-';

		return 1 + set_int(dest != NULL ? dest + 1 : NULL, -param);
	}
	else if (param >= 10)
		idx = set_int(dest, param / 10);
	else 
		idx = 0;
	if (dest != NULL)
		dest[idx] = (param % 10) + '0';
	return (++idx);
}

long	set_lowerhex(char *dest, unsigned int param)
{
	long	idx;

	idx = 0;
	if (param >= 16)
		idx = set_lowerhex(dest, param / 16);
	if (dest != NULL)
		dest[idx] = "0123456789abcdef"[param % 16];
	return (++idx);
}

long	set_upperhex(char *dest, unsigned int param)
{
	long	idx;

	idx = 0;
	if (param >= 16)
		idx = set_upperhex(dest, param / 16);
	if (dest != NULL)
		dest[idx] = "0123456789ABCDEF"[param % 16];
	return (++idx);
}

long	set_pointer(char *dest, uintptr_t param)
{
	long	idx;

	idx = 0;
	if (!param)
	{
		if (dest != NULL)
			ft_memcpy(dest, "(nil)", 5);
		return (5);
	}
	if (param >= 16)
	{
		idx = set_pointer(dest, param / 16);
	}
	else
	{
		if (dest != NULL)
		{
			dest[0] = '0';
			dest[1] = 'x';
		}
		idx = 2;
	}
	if (dest != NULL)
		dest[idx] = "0123456789abcdef"[param % 16];
	return (++idx);
}

long	set_unsignedint(char *dest, unsigned int param)
{
	long	idx;

	idx = 0;
	if (param >= 10)
		idx = set_unsignedint(dest, param / 10);
	if (dest != NULL)
		dest[idx] = (param % 10) + '0';
	return (++idx);
}
