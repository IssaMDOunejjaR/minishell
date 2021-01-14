/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:17:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/14 19:07:53 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_env_path(char **env)
{
	int		i;
	char	**tmp;
	
	i = 0;
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
		if (ft_strcmp(tmp[0], "PATH") == 0)
			break ;
		i++;
	}
	return (ft_split(tmp[1], ':'));
}

void	command_is_valid(t_cmd *cmd, char **env)
{	
	int		i;
	char	**env_path;
	DIR		*rep;
	struct	dirent	*read_dir;
	int		cmd_found;
	
	// free
	env_path = get_env_path(env);
	i = 0;
	cmd_found = 0;
	while (env_path[i] != NULL)
	{
		rep = opendir(env_path[i]);
		while ((read_dir = readdir(rep)) != NULL)
		{
			if (ft_strcmp(read_dir->d_name, cmd->cmds->content) == 0)
			{
				printf("found!\n");
				cmd_found = 1;
				break ;
			}
		}
		if (cmd_found == 1)
			break ;
		closedir(rep);
		i++;
	}
}

void	check_command(t_cmd *cmd, char **env)
{
	char *tmp;

	tmp = cmd->cmds->content;
	if (tmp[0] == '.' || tmp[0] == '/')
		printf("found . or /");
	else
		command_is_valid(cmd, env);
}