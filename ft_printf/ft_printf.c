/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:24:28 by user42            #+#    #+#             */
/*   Updated: 2024/08/14 17:31:14 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	set_char(char *dest, int param)
{
	if (dest != NULL)
		*dest = param;
	return (1);
}

long	set_string(char *dest, char *param)
{
	long	i;
	long	len;

	i = 0;
	if (!param)
	{
		if (dest != NULL)
			ft_memcpy(dest, "(null)", 6);
		return (6);
	}
	len = ft_strlen(param);
	while (i < len)
	{
		if (dest != NULL)
			dest[i] = param[i];
		i++;
	}
	return (i);
}

long	print_param(char **format, char *dest, va_list ap)
{
	long	ret;

	ret = 0;
	if ((*format)[1] == 'c')
		ret = set_char(dest, va_arg(ap, int));
	else if ((*format)[1] == 's')
		ret = set_string(dest, va_arg(ap, char *));
	else if ((*format)[1] == 'p')
		ret = set_pointer(dest, (uintptr_t)va_arg(ap, void *));
	else if ((*format)[1] == 'd' || (*format)[1] == 'i')
		ret = set_int(dest, va_arg(ap, int));
	else if ((*format)[1] == 'u')
		ret = set_unsignedint(dest, va_arg(ap, size_t));
	else if ((*format)[1] == 'x')
		ret = set_lowerhex(dest, va_arg(ap, size_t));
	else if ((*format)[1] == 'X')
		ret = set_upperhex(dest, va_arg(ap, size_t));
	else if ((*format)[1] == '%')
		ret = set_char(dest, '%');
	(*format)++;
	return (ret);
}

long	count_size(const char *format, va_list ap)
{
	long		index;
	long		size;
	const char	*cpy;

	index = 0;
	if (!format)
		return (-1);
	cpy = format;
	while (*cpy != '\0')
	{
		if (*cpy == '%')
		{
			size = print_param((char **)&cpy, NULL, ap);
			if (size < 0)
				return (size);
			index += size;
		}
		else
		{
			index++;
		}
		cpy++;
	}
	index++;
	return (index);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	long	size;
	char	*dest;

	va_start(ap, format);
	size = count_size(format, ap);
	if (size < 0)
		return (size);
	dest = malloc(size);
	size = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
			size += print_param((char **)&format, &dest[size], ap);
		else
			dest[size++] = *format;
		format++;
	}
	dest[size] = '\0';
	va_end(ap);
	print_str(dest, size);
	free(dest);
	return (size);
}
