/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:43:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 11:16:39 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*get_env_var(char **env, char *name)
{
	int		i;
	char	**tmp;
	char	*value;

	i = 0;
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
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

int					find_env_var(char **env, char *env_var)
{
	int		i;
	char	**tmp;
	char	**var;

	i = 0;
	var = ft_split(env_var, '=');
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
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

char				**change_env_var(char *env_var, char **env)
{
	char	**tmp;

	tmp = env;
	env = delete_env_var(env, env_var);
	env = tab_join(env, env_var);
	free_table(tmp);
	return (env);
}

static	t_list		*add_more_args(t_cmd *cmd, char **tmp)
{
	int		i;
	t_list	*new_lst;
	t_list	*t;

	i = 0;
	new_lst = NULL;
	while (tmp[i] != NULL)
	{
		ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup(tmp[i])));
		i++;
	}
	t = cmd->cmds;
	cmd->cmds = cmd->cmds->next;
	while (cmd->cmds != NULL)
	{
		ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup(cmd->cmds->content)));
		cmd->cmds = cmd->cmds->next;
	}
	cmd->cmds = t;
	return (new_lst);
}

t_list				*check_more_args(t_cmd *cmd)
{
	char	**tmp;
	t_list	*new_lst;

	tmp = ft_split(cmd->cmds->content, ' ');
	if (table_len_2d(tmp) > 1)
	{
		new_lst = add_more_args(cmd, tmp);
		free_commands(cmd);
	}
	else
	{
		free_table(tmp);
		return (cmd->cmds);
	}
	free_table(tmp);
	return (new_lst);
}