/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:15:06 by iounejja          #+#    #+#             */
/*   Updated: 2019/11/05 18:54:27 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		l_str;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	l_str = ft_strlen(s);
	str = malloc(sizeof(char) * (l_str + 1));
	if (!str)
		return (NULL);
	while (i < l_str)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
