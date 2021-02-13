/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 10:58:33 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 11:19:44 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *command, char *content, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (command != NULL)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
	}
	if (content != NULL)
	{
		ft_putstr_fd(content, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error != NULL)
		ft_putendl_fd(error, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
}

char	**get_args(t_cmd *cmd)
{
	int		i;
	char	**args;

	args = malloc(sizeof(char*) * (ft_lstsize(cmd->cmds) + 1));
	i = 0;
	while (cmd->cmds != NULL)
	{
		args[i] = ft_strdup(cmd->cmds->content);
		cmd->cmds = cmd->cmds->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**init_global(void)
{
	int		shell_lvl;
	char	*new_shellvl;
	char	*tmp;

	g_error_value = 0;
	g_latest_cmd = ft_strdup("minishell");
	g_old_pwd = ft_strdup("");
	g_env = change_env_var("OLDPWD");
	tmp = get_env_var("SHLVL");
	shell_lvl = ft_atoi(tmp) + 1;
	free(tmp);
	tmp = ft_itoa(shell_lvl);
	new_shellvl = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	g_env = change_env_var(new_shellvl);
	free(new_shellvl);
	return (g_env);
}

void	get_latest_cmd(t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->cmds;
	while (cmd->cmds->next != NULL)
		cmd->cmds = cmd->cmds->next;
	if (cmd->type != PIPE && g_prev_type != PIPE)
	{
		free(g_latest_cmd);
		g_latest_cmd = ft_strdup(cmd->cmds->content);
	}
	else
	{
		free(g_latest_cmd);
		g_latest_cmd = ft_strdup("");
	}
	cmd->cmds = tmp;
}
