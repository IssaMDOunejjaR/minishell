/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:10:03 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/06 10:56:52 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	ft_env(t_cmd *cmd, char **env)
{
	print_env(env);
	cmd->cmds = cmd->cmds->next;
	while (cmd->cmds != NULL)
	{
		ft_putendl_fd(cmd->cmds->content, 1);
		cmd->cmds = cmd->cmds->next;
	}
}