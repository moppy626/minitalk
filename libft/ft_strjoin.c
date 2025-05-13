/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:04:03 by user42            #+#    #+#             */
/*   Updated: 2024/06/17 21:38:15 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	char	*ret;

	s1len = 0;
	s2len = 0;
	if (s1)
		s1len = ft_strlen(s1);
	if (s2)
		s2len = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ret)
		return (NULL);
	if (s1)
		ft_memcpy(ret, s1, s1len);
	if (s2)
		ft_memcpy(ret + s1len, s2, s2len);
	ret[s1len + s2len] = '\0';
	return (ret);
}
