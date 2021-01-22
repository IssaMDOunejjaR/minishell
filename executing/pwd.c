/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issamdounejjar <issamdounejjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:53:34 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/22 18:05:28 by issamdounej      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_current_working_directory()
{
	char *cwd;
	char **tmp;
	
	cwd = getcwd(NULL, 0);
	if (ft_strcmp(cwd, "/") != 0)
		tmp = ft_split(cwd, '/');
	free(cwd);
	if (tmp == NULL)
		cwd = ft_strdup("/");
	else
	{
		cwd = ft_strdup(tmp[table_len_2d(tmp) - 1]);
		free_table(tmp);
	}
	return (cwd);
}