/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issamdounejjar <issamdounejjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:49:00 by issamdounej       #+#    #+#             */
/*   Updated: 2021/01/22 18:02:29 by issamdounej      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_command(t_cmd *cmd)
{
    // char **args;
    char *command;

    command = cmd->cmds->content;
    // cmd->cmds = cmd->cmds->next;
    char *args[] = {
        "-a",
        NULL
    };

    execve(command, args, NULL);
}