/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:17:00 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 11:20:56 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**set_oldpwd(void)
{
	char	*env_var;

	env_var = ft_strjoin("OLDPWD=", g_old_pwd);
	g_env = change_env_var(env_var);
	free(env_var);
	return (g_env);
}

static	char	**get_oldpwd(char *oldpwd)
{
	free(g_old_pwd);
	g_old_pwd = ft_strdup(oldpwd);
	if (find_env_var("OLDPWD") == 1)
		g_env = set_oldpwd();
	return (g_env);
}

static	char	*get_tmp(t_cmd *cmd)
{
	cmd->cmds = cmd->cmds->next;
	return (ft_strdup(cmd->cmds->content));
}

void			change_directory(t_cmd *cmd)
{
	char	*tmp;
	char	*oldpwd;
	t_list	*tmp_lst;

	g_error_value = 0;
	if (cmd->type == PIPE || g_prev_type == PIPE)
		;
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
		g_env = get_oldpwd(oldpwd);
	free(oldpwd);
	free(tmp);
	cmd->cmds = tmp_lst;
}
