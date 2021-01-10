/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:51:49 by iounejja          #+#    #+#             */
/*   Updated: 2019/11/05 18:50:11 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		begin(char const *s1, char const *set, int start)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		while (s1[start] == set[i])
		{
			i = 0;
			start++;
		}
		i++;
	}
	return (start);
}

static int		the_end(char const *s1, char const *set, int end)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		while (s1[end] == set[i])
		{
			i = 0;
			end--;
		}
		i++;
	}
	return (end);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	start;
	size_t	end;
	char	*str;

	i = 0;
	if (!s1)
		return (0);
	start = begin(s1, set, 0);
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	end = the_end(s1, set, ft_strlen(s1) - 1);
	str = malloc(sizeof(char) * ((end - start) + 2));
	if (!str)
		return (0);
	while (start <= end)
	{
		str[i++] = s1[start++];
	}
	str[i] = '\0';
	return (str);
}
