/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:11:08 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/10 15:15:08 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    lst_file_add_back(t_file **alst, t_file *new)
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