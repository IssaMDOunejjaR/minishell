/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:21:55 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/06 10:57:30 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**get_args(t_cmd *cmd)
{
	int		i;
	char 	**args;

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

void	command_exe(t_cmd *cmd, char **env)
{
	char	*command;
	char	**args;

	command = cmd->cmds->content;
	args = get_args(cmd);
	if (execve(command, args, env) != 0)
		ft_putendl_fd(strerror(errno), 1);
	free(command);
}