/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:51:57 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/08 15:05:34 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_file_add_back(t_file **alst, t_file *new)
{
	t_file *tmp;

	if (!alst || !new)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	tmp = (*alst);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
