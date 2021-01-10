/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:34:55 by iounejja          #+#    #+#             */
/*   Updated: 2019/11/03 16:16:31 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;
	size_t	ln;

	i = 0;
	if (!s)
		return (NULL);
	ln = ft_strlen(&s[start]);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	ln = (len <= ln) ? len : ln;
	str = malloc(sizeof(char) * (ln + 1));
	if (!str)
		return (NULL);
	while (len-- && s[start] != '\0')
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
