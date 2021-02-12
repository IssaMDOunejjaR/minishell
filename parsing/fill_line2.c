/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:23:40 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/12 17:17:26 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fill_d2(char *tmp, int *i)
{
	*i += ft_strlen(tmp);
	if (ft_strcmp(tmp, "OLDPWD") == 0)
		return (ft_strdup(g_old_pwd));
	else if (ft_strcmp(tmp, "_") == 0)
		return (ft_strdup(g_latest_cmd));
	else
		return (get_env_var( tmp));
}

void	fill_ret(char *vl_env, char *ret, int *j)
{
	while (vl_env[*j])
	{
		ret[*j] = vl_env[*j];
		(*j)++;
	}
}

void	free2(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

// void	fill_q2(char *line, int *i, int *k, char *ret)
// {
// 	int		j;
// 	char	*vl_env;
// 	char	*tmp;

// 	*i = *i + 1;
// 	if (line[*i] == '?')
// 	{
// 		*i = *i + 1;
// 		return (ft_itoa(g_error_value));
// 	}
// 	else if (ft_isdigit(line[*i]))
// 		*i = *i + 1;
// 	else
// 	{
// 		tmp = value_doll(line, *i);
// 		vl_env = fill_d2(tmp,  i);
// 		while (vl_env[j])
// 			ret[k++] = vl_env[j++];
// 		if (ft_strcmp(tmp, "") == 0)
// 			ret[k++] = '$';
// 		free2(tmp, vl_env);
// 	}
// }
