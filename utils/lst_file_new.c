/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:47:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/08 15:05:41 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_file	*lst_file_new(char *file, t_type type)
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
