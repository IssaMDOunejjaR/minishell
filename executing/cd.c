/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:17:00 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/06 16:41:46 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**set_oldpwd(char **env)
{
	char	*env_var;

	env_var = ft_strjoin("OLDPWD=", old_pwd);
	env = change_env_var(env_var, env);
	free(env_var);
	return (env);
}

static	char	**get_oldpwd(char **env, char *oldpwd)
{
	free(old_pwd);
	old_pwd = ft_strdup(oldpwd);
	if(find_env_var(env, "OLDPWD") == 1)
		env = set_oldpwd(env);
	return (env);
}

char	**change_directory(t_cmd *cmd, char **env)
{
	char	*tmp;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (ft_lstsize(cmd->cmds) > 1)
	{
		cmd->cmds = cmd->cmds->next;
		tmp = ft_strdup(cmd->cmds->content);
	}
	else
		tmp = ft_strdup("/");
	if (chdir(tmp) == -1)
	{
		g_error_value = 1;
		ft_putendl_fd(strerror(errno), 1);
	}
	else
		env = get_oldpwd(env, oldpwd);
	free(oldpwd);
	free(tmp);
	return (env);
}