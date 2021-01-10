/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:23:22 by iounejja          #+#    #+#             */
/*   Updated: 2019/11/03 18:20:52 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l_dest;
	size_t	l_src;
	size_t	l;

	i = 0;
	l_src = ft_strlen(src);
	if (!dst && size == 0)
		return (l_src);
	l_dest = ft_strlen(dst);
	l = l_dest;
	if (size <= l_dest)
		return (l_src + size);
	else
	{
		while (src[i] && l_dest < size - 1)
			dst[l_dest++] = src[i++];
		dst[l_dest] = '\0';
		return (l + l_src);
	}
}
