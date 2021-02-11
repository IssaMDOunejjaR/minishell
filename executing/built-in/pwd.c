/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:53:34 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 11:09:51 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_working_directory(void)
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

void	print_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		print_error("pwd", cwd, NULL);
	else
		ft_putendl_fd(cwd, 1);
	free(cwd);
}
