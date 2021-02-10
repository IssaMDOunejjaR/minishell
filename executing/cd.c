/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:17:00 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/10 12:02:11 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**set_oldpwd(char **env)
{
	char	*env_var;

	env_var = ft_strjoin("OLDPWD=", g_old_pwd);
	env = change_env_var(env_var, env);
	free(env_var);
	return (env);
}

static	char	**get_oldpwd(char **env, char *oldpwd)
{
	free(g_old_pwd);
	g_old_pwd = ft_strdup(oldpwd);
	if (find_env_var(env, "OLDPWD") == 1)
		env = set_oldpwd(env);
	return (env);
}

static	char	*get_tmp(t_cmd *cmd)
{
	cmd->cmds = cmd->cmds->next;
	return (ft_strdup(cmd->cmds->content));
}

char			**change_directory(t_cmd *cmd, char **env)
{
	char	*tmp;
	char	*oldpwd;
	t_list	*tmp_lst;

	if (cmd->type == PIPE || g_prev_type == PIPE)
		return (env);
	tmp_lst = cmd->cmds;
	oldpwd = getcwd(NULL, 0);
	if (ft_lstsize(cmd->cmds) > 1)
		tmp = get_tmp(cmd);
	else
		tmp = ft_strdup("/");
	if (chdir(tmp) == -1)
	{
		g_error_value = 1;
		print_error("cd", tmp, NULL);
	}
	else
		env = get_oldpwd(env, oldpwd);
	free(oldpwd);
	free(tmp);
	cmd->cmds = tmp_lst;
	return (env);
}
