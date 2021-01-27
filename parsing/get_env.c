/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:08:58 by ychennaf          #+#    #+#             */
/*   Updated: 2021/01/27 15:04:14 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env(char **env, char *line)
{
	char	*val_env;
	int		i;
	int		j;
	int		k;
	g_i++;
	i = 0;
	j = 0;
	while(line[g_i] != ' ' && line[g_i] != '\"' && line[g_i] != '\0' && line[g_i] != '$') //"$USER"
	{
		printf("c = %c, g_i = %d\n", line[g_i], g_i);
		i++;
		g_i++;
	}
	val_env = ft_substr(line, g_i - i, i);
	i--;
	// g_i--;
	while(env[j] != NULL)
	{
		k = 0;
		while(env[j][k] != '=')
		{
			if(val_env[k] != env[j][k])
				break;
			else if(k == i)
			{
				k = k + 2;
				i = k;
				while(env[j][k] != '\0')
					k++;
				val_env = ft_substr(env[j], i, k - i);
			}
			k++;
		}
		j++;
	}
	// while(env[j] != NULL)
	// 	printf("%s\n",env[j++]);
	// printf("$ = %s", val_env);
	// ft_lstadd_back(&cmd->cmds, ft_lstnew(val_env)); //echo "hello" "$USER"
	return (val_env);
}