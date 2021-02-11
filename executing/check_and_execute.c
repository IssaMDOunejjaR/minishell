/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:21:55 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 15:21:59 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**get_args(t_cmd *cmd)
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

char			**check_command(t_cmd *cmd, char **env)
{
	char	*tmp;

	if (cmd->files != NULL)
		if (check_files(cmd) == 1)
			return (env);
	if (cmd->cmds == NULL)
		return (env);
	tmp = cmd->cmds->content;
	if (tmp[0] == '.' || tmp[0] == '/')
		check_if_file_executable(cmd, env);
	else if (ft_strcmp(tmp, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(tmp, "pwd") == 0)
		print_pwd();
	else if (ft_strcmp(tmp, "env") == 0)
		print_env(env);
	else if (ft_strcmp(tmp, "export") == 0)
		print_export(env);
	else
		command_is_valid(cmd, env);
	return (env);
}

int				check_built_in(t_cmd *cmd)
{
	if (cmd->cmds == NULL)
		return (1);
	if (ft_strcmp(cmd->cmds->content, "cd") == 0 ||
	(ft_strcmp(cmd->cmds->content, "export") == 0
	&& ft_lstsize(cmd->cmds) > 1) ||
	ft_strcmp(cmd->cmds->content, "unset") == 0 ||
	ft_strcmp(cmd->cmds->content, "exit") == 0)
		return (1);
	return (0);
}

char			**exec_built_in(t_cmd *cmd, char **env)
{
	if (cmd->files != NULL)
		if (check_files(cmd) == 1)
			return (env);
	if (cmd->cmds == NULL)
		return (env);
	if (ft_strcmp(cmd->cmds->content, "cd") == 0)
		env = change_directory(cmd, env);
	else if (ft_strcmp(cmd->cmds->content, "export") == 0)
		env = ft_export(cmd, env);
	else if (ft_strcmp(cmd->cmds->content, "unset") == 0)
		env = ft_unset(cmd, env);
	else if (ft_strcmp(cmd->cmds->content, "exit") == 0)
		exit_shell(cmd, env);
	return (env);
}

void			command_exe(t_cmd *cmd, char **env)
{
	char	*command;
	char	**args;

	command = cmd->cmds->content;
	args = get_args(cmd);
	if (execve(command, args, env) != 0)
		g_error_value = 1;
}
