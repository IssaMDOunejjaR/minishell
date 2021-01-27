/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issamdounejjar <issamdounejjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:48:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/22 18:23:56 by issamdounej      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_shell()
{
    ft_putendl_fd("exit", 1);
    // free cmd
	free(g_cwd);
    exit(0);
}