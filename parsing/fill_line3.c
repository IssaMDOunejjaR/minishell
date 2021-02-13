/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 11:14:44 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/13 11:30:03 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_backslash2(char *line, int *i, char type)
{
	if (line[*i] == '\\' && check_backslash(line[*i + 1]) == 1 && type == '"')
	{
		(*i)++;
	}
	if (line[*i] && (check_backslash(line[*i]) == 0
		|| line[*i - 1] != '\\' || type == '"'))
		return (1);
	return (0);
}
