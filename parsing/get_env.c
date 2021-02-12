/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:08:58 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/12 17:17:30 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		end_doll(char c)
{
	int		i;
	char	*stop_char;

	i = 0;
	stop_char = " \"'$#%&()+,-./;:<>=?[]\\^{}~|0";
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
	int		check;

	j = i;
	check = 0;
	while (line[i] && !end_doll(line[i]))
		i++;
	tmp = ft_substr(line, j, i - j);
	val_env = get_env_var( tmp);
	j = ft_strlen(val_env);
	free(tmp);
	free(val_env);
	return (j);
}
