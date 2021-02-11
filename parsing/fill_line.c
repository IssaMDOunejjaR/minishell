/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:35:20 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/11 18:28:58 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_backslash(char c)
{
	if (c == '\\' || c == '"' || c == '$')
		return (1);
	return (0);
}

int		size_q_b(char *line, char **env, int i, char type)
{
	int		l;
	
	l = 0;
	while (line[i] && line[i] != type)//((line[i] != type && type == '"' && line[i - 1] != '\\') || (line[i] != type && type == '\''))
	{
		if (line[i] == '$' && type == '"' && line[i - 1] != '\\')
		{
			i++;
			l += get_env_length(env, line, i);
			i += value_doll_length(line, i);
		}else
		{
			if (line[i] != type && type == '\'')
			{
				i++;
				l++;
			}
			else
			{
				if (line[i] == '\\' && check_backslash(line[i + 1]) == 1 && type == '"')
					i++;
				if (line[i] && (check_backslash(line[i]) == 0 || line[i - 1] != '\\' || type == '"'))//line[i] && (check_backslash(line[i]) == 0 || line[i - 1] != '\\' || type == '"')
					l++;
				i++;
				
			}
		}
	}
	return (l);
}

char	*fill_d(char *line, char **env, int *i)
{
	char	*ret;
	char	*tmp;
	char	*vl_env;
	int		j;

	// printf("t");
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
	*i += ft_strlen(tmp);
	if (ft_strcmp(tmp, "OLDPWD") == 0)
		vl_env = ft_strdup(g_old_pwd);
	else if (ft_strcmp(tmp, "_") == 0)
		vl_env = ft_strdup(g_latest_cmd);
	else
		vl_env = get_env_var(env, tmp);
	ret = ft_calloc(ft_strlen(vl_env) + 1, sizeof(char));
	while(vl_env[j])
	{
		ret[j] = vl_env[j];
		j++;
	}
	if (ft_strcmp(tmp, "") == 0 && line[*i] != '"' && line[*i] != '$' && line[*i] != '\'')
		ret[j++] = '$';
	free(tmp);
	free(vl_env);
	return (ret);
}

char	*fill_q(char *line, char **env, int *i, char type)
{
	char	*ret;
	int		j;
	char	*tmp;
	char	*vl_env;
	int		k;

	j = *i;
	ret = ft_calloc(size_q_b(line, env, j, line[j - 1]) + 1, sizeof(char));
	k = 0;
	while (line[*i] && line[*i] != type)//((line[*i] != type || type == '"' || line[*i - 1] != '\\') || (line[*i] != type || type == '\''))
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
				if (ft_strcmp(tmp, "OLDPWD") == 0)
					vl_env = ft_strdup(g_old_pwd);
				else if (ft_strcmp(tmp, "_") == 0)
					vl_env = ft_strdup(g_latest_cmd);
				else
					vl_env = get_env_var(env, tmp);
				*i += ft_strlen(tmp);
				while (vl_env[j])
					ret[k++] = vl_env[j++];
				if (ft_strcmp(tmp, "") == 0)
					ret[k++] = '$';
				free(vl_env);
				free(tmp);	
			}
		}
		else
		{
			if (line[*i] != type && type == '\'')
			{
				ret[k++] = line[(*i)++];
			}
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