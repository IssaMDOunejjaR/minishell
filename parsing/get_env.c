/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:08:58 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/10 11:59:02 by ychennaf         ###   ########.fr       */
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

int		get_env_length(char **env, char *line, int i)
{
	char	*val_env;
	int		j;
	char	*tmp;
	int		check;

	j = i;
	check = 0;
	while (line[i] && !end_doll(line[i])) //"$USER"
		i++;
	tmp = ft_substr(line, j, i - j);
	val_env = get_env_var(env, tmp);
	j = ft_strlen(val_env);
	free(tmp);
	free(val_env);
	return (j);
}

void	add_lsdoll(char **env, char *line, t_cmd *cmd)
{
	char	*v_doll;
	char	*env_doll;

	g_i++;
	v_doll = value_doll(line, g_i);
	g_i += ft_strlen(v_doll) - 1;
	env_doll = get_env_var(env, v_doll);
	if (ft_strcmp(env_doll, ""))
		ft_lstadd_back(&cmd->cmds, ft_lstnew(env_doll));
	if (line[g_i + 1] == '\"' || line[g_i + 1] == '\'')
		;
	else if (ft_strcmp(v_doll, "") == 0 && line[g_i] == '$')
		ft_lstadd_back(&cmd->cmds, ft_lstnew("$"));
	free(v_doll);
}