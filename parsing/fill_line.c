/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:35:20 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/13 12:00:07 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_backslash(char c)
{
	if (c == '\\' || c == '"' || c == '$')
		return (1);
	return (0);
}

int		size_q_b2(char *line, int i, char type, int *l)
{
	if (line[i] == '\\' && check_backslash(line[i + 1]) == 1
		&& type == '"')
		i++;
	if (line[i] && (check_backslash(line[i]) == 0
		|| line[i - 1] != '\\' || type == '"'))
		(*l)++;
	i++;
	return (i);
}

int		size_q_b(char *line, int i, char type)
{
	int		l;

	l = 0;
	while (line[i] && line[i] != type)
	{
		if (line[i] == '$' && type == '"' && line[i - 1] != '\\')
		{
			l += get_env_length( line, ++i);
			i += value_doll_length(line, i);
		}
		else
		{
			if (line[i] != type && type == '\'')
			{
				i++;
				l++;
			}
			else
				i = size_q_b2(line, i, type, &l);
		}
	}
	return (l);
}

char	*fill_d(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*vl_env;
	int		j;

	j = 0;
	if (line[*i] == '?')
	{
		*i = *i + 1;
		return (ft_itoa(g_error_value));
	}
	if (ft_isdigit(line[*i]))
	{
		*i = *i + 1;
		return (ft_strdup(""));
	}
	tmp = value_doll(line, *i);
	vl_env = fill_d2(tmp,  i);
	ret = ft_calloc(ft_strlen(vl_env) + 1, sizeof(char));
	fill_ret(vl_env, ret, &j);
	if (ft_strcmp(tmp, "") == 0 && line[*i] != '"'
		&& line[*i] != '$' && line[*i] != '\'')
		ret[j++] = '$';
	free2(tmp, vl_env);
	return (ret);
}

char	*fill_q(char *line, int *i, char type)
{
	char	*ret;
	int		j;
	char	*tmp;
	char	*vl_env;
	int		k;

	j = *i;
	ret = ft_calloc(size_q_b(line,  j, line[j - 1]) + 1, sizeof(char));
	k = 0;
	while (line[*i] && line[*i] != type)
	{
		j = 0;
		if (line[*i] == '$' && type == '"' && line[*i - 1] != '\\')
		{
			*i = *i + 1;
			if (line[*i] == '?')
			{
				*i = *i + 1;
				return (ft_itoa(g_error_value));
			}
			else if (ft_isdigit(line[*i]))
				*i = *i + 1;
			else
			{
				tmp = value_doll(line, *i);
				vl_env = fill_d2(tmp,  i);
				while (vl_env[j])
					ret[k++] = vl_env[j++];
				if (ft_strcmp(tmp, "") == 0)
					ret[k++] = '$';
				free2(tmp, vl_env);
			}
		}
		else
		{
			if (line[*i] != type && type == '\'')
				ret[k++] = line[(*i)++];
			else
			{
				if (line[*i] == '\\' && check_backslash(line[*i + 1]) == 1 && type == '"')
					(*i)++;
				if (line[*i] && (check_backslash(line[*i]) == 0 || line[*i - 1] != '\\' || type == '"'))
					ret[k++] = line[*i];
				(*i)++;
			}
		}
	}
	*i = *i + 1;
	return (ret);
}
