/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:32:47 by ychennaf          #+#    #+#             */
/*   Updated: 2021/03/12 10:02:41 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
		|| line[i] == '\n' || line[i] == '\f' || line[i] == '\v')
		i++;
	return (i);
}

int		is_charm(char c)
{
	if (c == '|' || c == ';')
		return (1);
	return (0);
}

int		check_pipe(char *line, int i)
{
	i++;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == ';')
			return (0);
		else if ((line[i] != ' ' && line[i] != '\t'))
			return (i);
		i++;
	}
	return (0);
}

int		check_app(char *line, int i)
{
	int		j;

	j = 0;
	i++;
	while (line[i] == '>')
	{
		i++;
		j++;
	}
	if (j > 1)
		return (0);
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '|' || line[i] == ';')
			return (0);
		else if ((line[i] != ' ' && line[i] != '\t'))
			return (i);
		i++;
		if (line[i] == '>')
			return (0);
	}
	return (0);
}

int		check_semi(char *line, int i)
{
	i++;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == ';')
			return (0);
		else if (line[i] == '\0' || (line[i] != ' ' && line[i] != '\t'))
			return (i);
		i++;
	}
	return (i);
}
