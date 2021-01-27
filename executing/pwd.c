/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:53:34 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/27 16:23:27 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_current_working_directory()
{
	char *cwd;
	char **tmp;
	
	cwd = getcwd(NULL, 0);
	tmp = ft_split(cwd, '/');
	free(cwd);
	if (ft_strcmp(cwd, "/") == 0)
		cwd = ft_strdup("/");
	else
		cwd = ft_strdup(tmp[table_len_2d(tmp) - 1]);
	free_table(tmp);
	return (cwd);
}