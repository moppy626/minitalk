/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:28:15 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/15 22:39:48 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include "../libft/libft.h"

void			*ft_memcpy(void *dest, const void *src, size_t n);
void			print_str(char *s, long size);
long			set_int(char *dest, int param);
long			set_lowerhex(char *dest, unsigned int param);
long			set_upperhex(char *dest, unsigned int param);
long			set_pointer(char *dest, uintptr_t param);
long			set_unsignedint(char *dest, unsigned int param);
int				ft_printf(const char *format, ...);

#endif