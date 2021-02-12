/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 12:00:23 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/11 18:56:38 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		size_q(char *line, char **env, int *i, char type)
{
	int		l;

	l = 0;
	while (line[*i] && line[*i] != type)//((line[*i] != type && type == '"' && line[*i - 1] != '\\') || (line[*i] != type && type == '\''))
	{
		if (line[*i] == '$' && type == '"' && line[*i - 1] != '\\')
		{
			*i = *i + 1;
			l += get_env_length(env, line, *i);
			*i += value_doll_length(line, *i);
		}else
		{
			if (line[*i] != type && type == '\'')
			{
				l++;
				(*i)++;
			}
			else
			{
				if (line[*i] == '\\' && check_backslash(line[*i + 1]) == 1 && type == '"')
					(*i)++;
				if (line[*i] && (check_backslash(line[*i]) == 0 || line[*i - 1] != '\\' || type == '"')) //((line[*i] != type && type == '\'') || (line[*i] != type || type != '"' || line[*i - 1] != '\\'))
					l++;
				(*i)++;
			}
		}
	}
	return (l);
}

int		size_line(char *line, char **env)
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
			i++;
			l += get_env_length(env, line, i);
			i += value_doll_length(line, i);
		}
		else if (line[i] == '\'' || line[i] == '"')
		{
			type = line[i++];
			l += size_q(line, env, &i, type);
		}
		else if (line[i])
		{
			i++;
			l++;
		}
		// printf("here --> |%c|\n", line[i]);
	}
	return (l);
}

int		check_end_cmd(t_cmd *cmd, char **tab, char **env)
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
	if (ft_strcmp(tab[g_t], ">") == 0)
	{
		g_t++;
		lst_file_add_back(&cmd->files, lst_file_new(handle_file(tab[g_t++], env), WRITE));
		//func addback_file = tab[g_t];
		return (0);
	}
	else if (ft_strcmp(tab[g_t], "<") == 0)
	{
		g_t++;
		lst_file_add_back(&cmd->files, lst_file_new(handle_file(tab[g_t++], env), READ));
		//func addback_file = tab[g_t];
		return (0);
	}
	else if (ft_strcmp(tab[g_t], ">>") == 0)
	{
		g_t++;
		lst_file_add_back(&cmd->files, lst_file_new(handle_file(tab[g_t++], env), APPEND));
		//func addback_file = tab[g_t];
		return (0);
	}
	return (0);
}

void	handle_cmd(char *line, char **env, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;
	int		k;

	j = 0;
	i = 0;
	// printf("i = |%d|\n", size_line(line,env));
	ret = ft_calloc(size_line(line, env) + 1, sizeof(char));
	while (line[i])
	{
		k = 0;
		if (line[i] == '"' || line[i] == '\'')
		{
			i++;
			// printf("line = |%c|\n",line[i]);
			tmp = fill_q(line, env, &i, line[i - 1]);
			while(tmp[k])
				ret[j++] = tmp[k++];
			free(tmp);
		}
		else if (line[i] == '$')
		{
			i++;
			tmp = fill_d(line, env, &i);
			while(tmp[k])
				ret[j++] = tmp[k++];
			free(tmp);
		}
		else if (line[i])
			ret[j++] = line[i++];
	}
	// printf("ret = |%s|\n",ret);
	ft_lstadd_back(&cmd->cmds, ft_lstnew(ret));
	// free(ret);
}

char	*handle_file(char *line, char **env)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;
	int		k;

	j = 0;
	i = 0;
	// printf("i = |%d|\n", size_line(line,env));
	ret = ft_calloc(size_line(line, env) + 1, sizeof(char));
	while (line[i])
	{
		k = 0;
		if (line[i] == '"' || line[i] == '\'')
		{
			i++;
			// printf("line = |%c|\n",line[i]);
			tmp = fill_q(line, env, &i, line[i - 1]);
			while(tmp[k])
				ret[j++] = tmp[k++];
			free(tmp);
		}
		else if (line[i] == '$')
		{
			i++;
			tmp = fill_d(line, env, &i);
			while(tmp[k])
				ret[j++] = tmp[k++];
			free(tmp);
		}
		else if (line[i])
			ret[j++] = line[i++];
	}
	// printf("ret = |%s|\n",ret);
	return (ret);
	// free(ret);
}