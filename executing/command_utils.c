/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:47:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/06 18:38:43 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char **env, char *name)
{
	int		i;
	char	**tmp;
	char	*value;
	
	i = 0;
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
		if (ft_strcmp(tmp[0], name) == 0)
		{
			value = ft_strdup(tmp[1]);
			free_table(tmp);
			return (value);
		}
		free_table(tmp);
		i++;
	}
	return (ft_strdup(""));
}

int		find_env_var(char **env, char *env_var)
{
	int		i;
	char	**tmp;
	char	**var;

	i = 0;
	var = ft_split(env_var, '=');
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
		if (ft_strcmp(var[0], tmp[0]) == 0)
		{
			free_table(var);
			free_table(tmp);
			return (1);
		}
		free_table(tmp);
		i++;
	}
	free_table(var);
	return (0);
}

char	**change_env_var(char *env_var, char **env)
{
	char	**tmp;
	
	tmp = env;
	env = delete_env_var(env, env_var);
	env = tab_join(env, env_var);
	free_table(tmp);
	return (env);
}

void	free_commands(t_cmd *cmd)
{
	while (cmd->cmds != NULL)
	{
		free(cmd->cmds->content);
		free(cmd->cmds);
		cmd->cmds = cmd->cmds->next;
	}
	while (cmd->files != NULL)
	{
		free(cmd->files->file);
		free(cmd->files);
		cmd->files = cmd->files->next;
	}
}

int		check_special_carac(char *str)
{
	int		i;
	int		j;
	char	*sc;

	sc = "!#%&()*+,-./:=?@[]^{}~";
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (sc[j] != '\0')
		{
			if (str[i] == sc[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		is_all_num(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}