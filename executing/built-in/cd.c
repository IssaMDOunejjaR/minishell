/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:17:00 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 14:45:17 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**set_oldpwd(char **env)
{
	char	*env_var;

	env_var = ft_strjoin("OLDPWD=", g_old_pwd);
	g_env = change_env_var(env_var, g_env);
	free(env_var);
	return (g_env);
}

static	char	**get_oldpwd(char *oldpwd)
{
	free(g_old_pwd);
	g_old_pwd = ft_strdup(oldpwd);
	if (find_env_var( "OLDPWD") == 1)
		g_env = set_oldpwd(g_env);
	return (g_env);
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

	g_error_value = 0;
	if (cmd->type == PIPE || g_prev_type == PIPE)
		return (g_env);
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
		g_env = get_oldpwd( oldpwd);
	free(oldpwd);
	free(tmp);
	cmd->cmds = tmp_lst;
	return (g_env);
}
