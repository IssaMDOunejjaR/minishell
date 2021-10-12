/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:53:34 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/17 11:54:47 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_working_directory(void)
{
	char *cwd;
	char **tmp;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		if (g_old_cwd != NULL)
			cwd = ft_strdup(g_old_cwd);
	if (g_old_cwd != NULL)
		free(g_old_cwd);
	g_old_cwd = ft_strdup(cwd);
	if (cwd == NULL)
		cwd = ft_strdup(g_old_cwd);
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

	g_error_value = 0;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		ft_putendl_fd(g_old_cwd, 1);
	else
		ft_putendl_fd(cwd, 1);
	free(cwd);
}
