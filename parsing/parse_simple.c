/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:45:06 by ychennaf          #+#    #+#             */
/*   Updated: 2021/01/16 17:54:03 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_simple_s(char *line)
{
	int i;

	i = 0;
	while (line[g_i] != '\0' && line[g_i] != ' ')
	{
		g_i++;
		i++;
	}
	
	return(ft_substr(line, g_i - i, i));
}