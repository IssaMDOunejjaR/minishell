/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:53:34 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/17 15:05:08 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_current_working_directory()
{
	char **tmp;
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	tmp = ft_split(cwd, '/');
	if (tmp[table_len_2d(tmp) - 1] != NULL)
		cwd = ft_strdup(tmp[table_len_2d(tmp) - 1]);
	if (cwd == NULL)
		cwd = ft_strdup("/");
	free_table(tmp);
	return (cwd);
}

void	print_cwd()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
}