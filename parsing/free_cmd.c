/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:33:00 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/11 10:45:07 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_commands(t_cmd *cmd)
{
    while (cmd->cmds != NULL)
    {
        free(cmd->cmds->content);
        free(cmd->cmds);
        cmd->cmds = cmd->cmds->next;
    }
    while (cmd->files != NULL)
    {
        free(cmd->files->file);
        free(cmd->files);
        cmd->files = cmd->files->next;
    }
}