/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:43:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/14 11:05:01 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*get_env_var(char *name)
{
	int		i;
	char	**tmp;
	char	*value;

	i = 0;
	while (g_env[i] != NULL)
	{
		tmp = ft_split(g_env[i], '=');
		if (ft_strcmp(tmp[0], name) == 0)
		{
			value = ft_strdup(tmp[1]);
			free_table(tmp);
			return (value);
		}
		free_table(tmp);
		i++;
	}
	return (ft_strdup(""));
}

int					find_env_var(char *env_var)
{
	int		i;
	char	**tmp;
	char	**var;

	i = 0;
	var = ft_split(env_var, '=');
	while (g_env[i] != NULL)
	{
		tmp = ft_split(g_env[i], '=');
		if (ft_strcmp(var[0], tmp[0]) == 0)
		{
			free_table(var);
			free_table(tmp);
			return (1);
		}
		free_table(tmp);
		i++;
	}
	free_table(var);
	return (0);
}

char				**change_env_var(char *env_var)
{
	char	**tmp;

	tmp = g_env;
	g_env = delete_env_var(env_var);
	g_env = tab_join(g_env, env_var);
	free_table(tmp);
	return (g_env);
}

int					get_write_append_read(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->files->type == WRITE)
		fd = open(cmd->files->file, O_CREAT | O_TRUNC, 0666);
	else if (cmd->files->type == APPEND)
		fd = open(cmd->files->file, O_CREAT, 0666);
	else if (cmd->files->type == READ)
	{
		fd = open(cmd->files->file, O_RDONLY, 0666);
		if (fd < 0)
		{
			if (cmd->cmds != NULL)
				print_error(cmd->cmds->content, cmd->files->file, NULL);
			else
				print_error(NULL, cmd->files->file, NULL);
		}
	}
	return (fd);
}
