/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:48:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/10 12:02:11 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_shell(t_cmd *cmd, char **env)
{
	t_list *tmp;

	tmp = cmd->cmds;
	if (cmd->type != PIPE && g_prev_type != PIPE)
		ft_putendl_fd("exit", 1);
	cmd->cmds = cmd->cmds->next;
	if (cmd->cmds != NULL)
	{
		if (is_all_num(cmd->cmds->content) == 1)
		{
			print_error("exit", cmd->cmds->content,
			"numeric argument required");
			g_error_value = 255;
		}
		else
			g_error_value = ft_atoi(cmd->cmds->content);
	}
	cmd->cmds = tmp;
	if (cmd->type != PIPE && g_prev_type != PIPE)
	{
		free(g_cwd);
		free_table(env);
		free_commands(cmd);
		exit(g_error_value);
	}
}
