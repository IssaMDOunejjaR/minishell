/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:19:05 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/13 15:27:26 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		value_doll_length(char *line, int i)
{
	int	j;

	j = 0;
	if (line[i] == '?')
		return (1);
	while (line[i] && !end_doll(line[i]))
	{
		i++;
		j++;
	}
	return (j);
}

char	*value_doll(char *line, int i)
{
	char	*a_doll;
	int		j;

	j = value_doll_length(line, i);
	a_doll = ft_substr(line, i, j);
	return (a_doll);
}
