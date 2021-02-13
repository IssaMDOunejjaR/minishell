/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:10:03 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 11:27:14 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(void)
{
	int		i;
	char	**tmp;

	g_error_value = 0;
	i = 0;
	while (g_env[i] != NULL)
	{
		tmp = ft_split(g_env[i], '=');
		if (table_len_2d(tmp) > 1)
			ft_putendl_fd(g_env[i], 1);
		free_table(tmp);
		i++;
	}
}
