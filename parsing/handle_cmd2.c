/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:37:48 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/12 17:17:56 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		size_q2(char *line, int *i, char type)
{
	int		l;

	l = 0;
	if (line[*i] == '\\' && check_backslash(line[*i + 1]) == 1 && type == '"')
		(*i)++;
	if (line[*i] && (check_backslash(line[*i]) == 0
		|| line[*i - 1] != '\\' || type == '"'))
		l++;
	(*i)++;
	return (l);
}

int		check_end_cmd2(t_cmd *cmd, char **tab)
{
	if (ft_strcmp(tab[g_t], "|") == 0)
	{
		cmd->type = PIPE;
		g_t++;
		return (1);
	}
	if (ft_strcmp(tab[g_t], ";") == 0)
	{
		cmd->type = END;
		g_t++;
		return (1);
	}
	return (0);
}

void	handle2(char *tmp, char *ret, int *j)
{
	int	k;

	k = 0;
	while (tmp[k])
		ret[(*j)++] = tmp[k++];
	free(tmp);
}

int		fill_qd(char **tmp, char *line, int i)
{
	if (line[i] == '"' || line[i] == '\'')
	{
		i++;
		*tmp = fill_q(line,  &i, line[i - 1]);
	}
	else if (line[i] == '$')
	{
		i++;
		*tmp = fill_d(line,  &i);		
	}
	return (i);
}
