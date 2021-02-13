/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:48:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 17:06:06 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_and_exit(t_cmd *cmd)
{
	free(g_cwd);
	free(g_latest_cmd);
	free_table(g_env);
	free_commands(cmd);
	exit(g_error_value);
}

void			exit_shell(t_cmd *cmd)
{
	t_list *tmp;

	g_error_value = 0;
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
		free_and_exit(cmd);
}
