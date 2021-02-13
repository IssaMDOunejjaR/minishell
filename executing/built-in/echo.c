/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:38:44 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 10:56:52 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_option(char *str)
{
	int		i;

	if (str[0] == '-')
	{
		i = 1;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int		check;

	g_error_value = 0;
	check = 0;
	cmd->cmds = cmd->cmds->next;
	while (cmd->cmds != NULL)
	{
		if (check_option(cmd->cmds->content) == 1)
			break ;
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
