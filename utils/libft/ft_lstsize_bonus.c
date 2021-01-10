/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:05:14 by iounejja          #+#    #+#             */
/*   Updated: 2019/11/06 14:30:54 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int count;

	if (!lst)
		return (0);
	count = 0;
	if (lst)
	{
		while (lst != NULL)
		{
			count++;
			lst = lst->next;
		}
	}
	return (count);
}
