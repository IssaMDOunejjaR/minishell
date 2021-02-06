/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:53:34 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/06 10:46:49 by iounejja         ###   ########.fr       */
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

void	print_pwd()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		ft_putendl_fd(strerror(errno), 1);
	else
		ft_putendl_fd(cwd, 1);
	free(cwd);
}