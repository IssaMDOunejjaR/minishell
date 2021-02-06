/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:48:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/06 18:39:26 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_shell(t_cmd *cmd, char **env)
{
	t_list *tmp;

	tmp = cmd->cmds;
	if (ft_lstsize(cmd->cmds) <= 2)
	{
		ft_putendl_fd("exit", 1);
		cmd->cmds = cmd->cmds->next;
		if (cmd->cmds != NULL)
		{
			if (is_all_num(cmd->cmds->content) == 1)
			{
				ft_putendl_fd("numeric argument required", 1);
				g_error_value = 255;
			}
			else
				g_error_value = ft_atoi(cmd->cmds->content);
		}
		cmd->cmds = tmp;
		free(g_cwd);
		free_table(env);
		free_commands(cmd);
		exit(g_error_value);
	}
	else
		ft_putendl_fd("too many arguments!", 1);
}