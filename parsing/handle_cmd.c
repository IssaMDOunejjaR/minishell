/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 12:00:23 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/13 16:48:33 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		size_q(char *line, int *i, char type)
{
	int		l;

	l = 0;
	while (line[*i] && line[*i] != type)
	{
		if (line[*i] == '$' && type == '"' && line[*i - 1] != '\\')
		{
			l += get_env_length(line, ++(*i));
			*i += value_doll_length(line, *i);
		}
		else
		{
			if (line[*i] != type && type == '\'')
			{
				l++;
				(*i)++;
			}
			else
				l += size_q2(line, i, type);
		}
	}
	return (l);
}

int		size_line(char *line)
{
	int		i;
	int		l;
	char	type;

	i = 0;
	l = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			l += get_env_length(line, ++i);
			i += value_doll_length(line, i);
		}
		else if (line[i] == '\'' || line[i] == '"')
		{
			type = line[i++];
			l += size_q(line, &i, type);
		}
		else if (line[i])
		{
			i++;
			l++;
		}
	}
	return (l);
}

int		check_end_cmd(t_cmd *cmd, char **tab)
{
	if (check_end_cmd2(cmd, tab) == 1)
		return (1);
	if (ft_strcmp(tab[g_t], ">") == 0)
	{
		g_t++;
		lst_file_add_back(&cmd->files,
		lst_file_new(handle_file(tab[g_t++]), WRITE));
	}
	else if (ft_strcmp(tab[g_t], "<") == 0)
	{
		g_t++;
		lst_file_add_back(&cmd->files,
		lst_file_new(handle_file(tab[g_t++]), READ));
	}
	else if (ft_strcmp(tab[g_t], ">>") == 0)
	{
		g_t++;
		lst_file_add_back(&cmd->files,
		lst_file_new(handle_file(tab[g_t++]), APPEND));
	}
	return (0);
}

void	handle_cmd(char *line, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;

	j = 0;
	i = 0;
	ret = ft_calloc(size_line(line) + 1, sizeof(char));
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = fill_qd(&tmp, line, i);
			handle2(tmp, ret, &j);
		}
		else if (line[i] == '$')
		{
			i = fill_qd(&tmp, line, i);
			handle2(tmp, ret, &j);
		}
		else if (line[i])
			ret[j++] = line[i++];
	}
	ft_lstadd_back(&cmd->cmds, ft_lstnew(ret));
}

char	*handle_file(char *line)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;

	j = 0;
	i = 0;
	ret = ft_calloc(size_line(line) + 1, sizeof(char));
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = fill_qd(&tmp, line, i);
			handle2(tmp, ret, &j);
		}
		else if (line[i] == '$')
		{
			i = fill_qd(&tmp, line, i);
			handle2(tmp, ret, &j);
		}
		else if (line[i])
			ret[j++] = line[i++];
	}
	return (ret);
}
