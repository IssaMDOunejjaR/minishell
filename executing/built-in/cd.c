/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:17:00 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/15 12:40:47 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	set_oldpwd(void)
{
	char	*env_var;

	env_var = ft_strjoin("OLDPWD=", g_old_pwd);
	g_env = change_env_var(env_var);
	free(env_var);
}

static	void	get_oldpwd(char *oldpwd)
{
	free(g_old_pwd);
	g_old_pwd = ft_strdup(oldpwd);
	if (find_env_var("OLDPWD") == 1)
		set_oldpwd();
}

static	char	*get_tmp(t_cmd *cmd)
{
	cmd->cmds = cmd->cmds->next;
	if (ft_strcmp(cmd->cmds->content, "-") == 0)
	{
		if (ft_strcmp(g_old_pwd, "") == 0)
		{
			print_error("cd", NULL, "OLDPWD not set");
			return (ft_strdup(""));
		}
		else
		{
			ft_putendl_fd(g_old_pwd, 1);
			return (ft_strdup(g_old_pwd));
		}
	}
	return (ft_strdup(cmd->cmds->content));
}

static	int		empty_path(char *tmp, char *oldpwd)
{
	if (ft_strcmp(tmp, "") == 0)
		return (1);
	if (chdir(tmp) == -1)
	{
		g_error_value = 1;
		print_error("cd", tmp, NULL);
	}
	else
		get_oldpwd(oldpwd);
	return (0);
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
	if (oldpwd == NULL)
		oldpwd = ft_strdup(g_old_pwd);
	if (ft_lstsize(cmd->cmds) > 1)
		tmp = get_tmp(cmd);
	else
		tmp = get_env_var("HOME");
	if (empty_path(tmp, oldpwd) == 1)
	{
		free(oldpwd);
		free(tmp);
		cmd->cmds = tmp_lst;
		return ;
	}
	free(oldpwd);
	free(tmp);
	cmd->cmds = tmp_lst;
}
