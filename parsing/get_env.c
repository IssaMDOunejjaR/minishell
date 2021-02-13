/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:08:58 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/13 15:21:06 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		lenght_digit(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		end_doll(char c)
{
	int		i;
	char	*stop_char;

	i = 0;
	stop_char = " \"'$#%&()+,-./;:<>=[]\\^{}~|0";
	while (stop_char[i] != '\0')
	{
		if (stop_char[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		get_env_length(char *line, int i)
{
	char	*val_env;
	int		j;
	char	*tmp;

	j = i;
	if (line[i] == '?')
		return (lenght_digit(g_error_value));
	while (line[i] && !end_doll(line[i]))
		i++;
	tmp = ft_substr(line, j, i - j);
	if (ft_strcmp(tmp, "OLDPWD") == 0)
		j = ft_strlen(g_old_pwd);
	else if (ft_strcmp(tmp, "_") == 0)
		j = ft_strlen(g_latest_cmd);
	else
	{
		val_env = get_env_var(tmp);
		j = ft_strlen(val_env);
		free(val_env);
	}
	free(tmp);
	return (j);
}
