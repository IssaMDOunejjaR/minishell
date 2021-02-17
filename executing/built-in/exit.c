/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:48:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/17 10:37:10 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_and_exit(t_cmd *cmd)
{
	free(g_cwd);
	free(g_latest_cmd);
	free_table(g_env);
	free_commands(cmd);
	if (g_old_cwd != NULL)
		free(g_old_cwd);
	if (!g_prev_pwd)
		free(g_prev_pwd);
	exit(g_error_value);
}

static	void	check_before_exit(t_cmd *cmd)
{
	g_error_value = 0;
	if (cmd->type != PIPE && g_prev_type != PIPE)
		ft_putendl_fd("exit", 1);
}

void			exit_shell(t_cmd *cmd)
{
	t_list *tmp;

	check_before_exit(cmd);
	tmp = cmd->cmds;
	cmd->cmds = cmd->cmds->next;
	if (ft_lstsize(cmd->cmds) > 1)
	{
		print_error("exit", NULL, "too many arguments");
		return ;
	}
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
