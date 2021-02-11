/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:10:26 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/10 15:15:05 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_file  *lst_file_new(char *file, t_type type)
{
    t_file *new;
    new = malloc(sizeof(t_file));
    if (new)
    {
        new->file = file;
        new->type = type;
        new->next = NULL;
    }
    return (new);
}