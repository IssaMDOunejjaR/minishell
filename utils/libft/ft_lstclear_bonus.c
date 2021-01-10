/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:01:48 by iounejja          #+#    #+#             */
/*   Updated: 2019/11/06 16:02:21 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *list;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		list = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = list;
	}
}
