/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:21:27 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/13 17:13:38 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			init_cmd(t_cmd *cmd)
{
	cmd->files = NULL;
	cmd->cmds = NULL;
	cmd->type = END;
}

static	int		check_line3(char *line, int i, int *check)
{
	char	type;

	type = line[i++];
	while (line[i])
	{
		if ((line[i] == type && type == '"' && line[i - 1] != '\\')
			|| (line[i] == type && type == '\''))
		{
			(*check)++;
			i++;
			break ;
		}
		if (line[i])
			i++;
	}
	return (i);
}

static	int		check_line2(char *line, int *i)
{
	if (line[*i] == '|')
	{
		if (check_pipe(line, *i) == 0)
			return (0);
		else
			*i = check_pipe(line, *i);
	}
	else if (line[*i] == '>' || line[*i] == '<')
	{
		if (check_app(line, *i) == 0)
			return (0);
		else
			*i = check_app(line, *i);
	}
	else if (line[*i] == ';')
	{
		if (check_semi(line, *i) == 0)
			return (0);
		else
			*i = check_semi(line, *i);
	}
	return (1);
}

int				check_line(char *line)
{
	int		i;
	int		check;

	i = 0;
	i = skip_spaces(line, i);
	if (is_charm(line[i]) == 1)
		return (1);
	while (line[i])
	{
		check = 0;
		if (line[i] == '\'' || line[i] == '"')
		{
			i = check_line3(line, i, &check);
			if (check == 0)
				return (1);
		}
		else if (check_line2(line, &i) == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

int				get_command(t_cmd *cmd, char **tab2)
{
	int		i;

	i = 1;
	init_cmd(cmd);
	while (tab2[g_t])
	{
		if (check_end_cmd(cmd, tab2) == 1)
			return (1);
		else if (tab2[g_t] && (ft_strcmp(tab2[g_t], ">")
			&& ft_strcmp(tab2[g_t], ";")
			&& ft_strcmp(tab2[g_t], "<")
			&& ft_strcmp(tab2[g_t], ">>")))
			handle_cmd(tab2[g_t++], cmd);
	}
	return (2);
}
