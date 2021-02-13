/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:38:44 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 14:45:25 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int		check;

	check = 0;
	g_error_value = 0;
	cmd->cmds = cmd->cmds->next;
	while (cmd->cmds != NULL && ft_strncmp(cmd->cmds->content, "-n", 2) == 0)
	{
		check = 1;
		cmd->cmds = cmd->cmds->next;
	}
	while (cmd->cmds != NULL)
	{
		ft_putstr_fd(cmd->cmds->content, 1);
		if (cmd->cmds->next != NULL)
			ft_putstr_fd(" ", 1);
		cmd->cmds = cmd->cmds->next;
	}
	if (check == 0)
		ft_putchar_fd('\n', 1);
}
