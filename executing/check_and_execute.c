/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:21:55 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/14 11:01:20 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_more(t_cmd *cmd)
{
	if (cmd->files != NULL)
		if (check_files(cmd) == 1)
			return (1);
	if (cmd->cmds == NULL)
		return (1);
	if (ft_strcmp(cmd->cmds->content, "/") == 0)
	{
		g_error_value = 126;
		print_error(cmd->cmds->content, NULL, "is a directory");
		return (1);
	}
	return (0);
}

void	check_command(t_cmd *cmd)
{
	char	*tmp;

	tmp = cmd->cmds->content;
	if (check_more(cmd) == 1)
		;
	else if (tmp[0] == '.' || tmp[0] == '/')
		check_if_file_executable(cmd);
	else if (ft_strcmp(tmp, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(tmp, "pwd") == 0)
		print_pwd();
	else if (ft_strcmp(tmp, "env") == 0)
		print_env();
	else if (ft_strcmp(tmp, "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->cmds->content, "cd") == 0)
		change_directory(cmd);
	else if (ft_strcmp(cmd->cmds->content, "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->cmds->content, "exit") == 0)
		exit_shell(cmd);
	else
		command_is_valid(cmd);
}

int		check_built_in(t_cmd *cmd)
{
	if (cmd->cmds == NULL)
		return (1);
	if (cmd->type != PIPE && g_prev_type != PIPE)
	{
		if (ft_strcmp(cmd->cmds->content, "cd") == 0 ||
		(ft_strcmp(cmd->cmds->content, "export") == 0
		&& ft_lstsize(cmd->cmds) > 1) ||
		ft_strcmp(cmd->cmds->content, "unset") == 0 ||
		ft_strcmp(cmd->cmds->content, "exit") == 0)
			return (1);
	}
	return (0);
}

void	exec_built_in(t_cmd *cmd)
{
	if (cmd->files != NULL)
		if (check_files(cmd) == 1)
			return ;
	if (cmd->cmds == NULL)
		return ;
	if (ft_strcmp(cmd->cmds->content, "cd") == 0)
		change_directory(cmd);
	else if (ft_strcmp(cmd->cmds->content, "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->cmds->content, "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->cmds->content, "exit") == 0)
		exit_shell(cmd);
}

void	command_exe(t_cmd *cmd)
{
	char	*command;
	char	**args;

	command = cmd->cmds->content;
	args = get_args(cmd);
	if (execve(command, args, g_env) != 0)
		g_error_value = 1;
}
