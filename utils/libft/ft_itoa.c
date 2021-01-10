/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:38:32 by iounejja          #+#    #+#             */
/*   Updated: 2019/10/30 20:31:42 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len_digit(long int nb)
{
	int l;

	if (nb == 0)
		return (1);
	l = 0;
	if (nb < 0)
	{
		nb = -nb;
		l++;
	}
	while (nb > 0)
	{
		nb /= 10;
		l++;
	}
	return (l);
}

char			*ft_itoa(int n)
{
	long	nb;
	int		count;
	char	*str;

	nb = n;
	count = len_digit(nb);
	if (!(str = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	str[count--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[count--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
