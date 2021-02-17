/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:54:22 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/17 11:58:39 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		len_home(char *str)
{
	int i;
	int l;

	l = 0;
	i = 1;
	while (str[i] != '\0')
	{
		i++;
		l++;
	}
	return (l);
}

char			*get_home_dir(char *str)
{
	char	*home;
	int		i;
	int		j;
	char	*tmp;

	tmp = get_env_var("HOME");
	home = malloc(sizeof(char) * (len_home(str) + ft_strlen(tmp) + 1));
	i = 0;
	while (tmp[i] != '\0')
	{
		home[i] = tmp[i];
		i++;
	}
	j = 1;
	while (str[j] != '\0')
	{
		home[i] = str[j];
		i++;
		j++;
	}
	home[i] = '\0';
	free(tmp);
	return (home);
}

void			free_cd(char *oldpwd, char *tmp)
{
	free(oldpwd);
	free(tmp);
}

void			save_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp != NULL)
	{
		free(g_prev_pwd);
		g_prev_pwd = ft_strdup(tmp);
	}
	else if (tmp == NULL && g_prev_pwd != NULL)
	{
		free(tmp);
		tmp = g_prev_pwd;
		g_prev_pwd = ft_strdup(g_prev_pwd);
	}
	free(tmp);
}
