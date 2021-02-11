/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:17:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 11:16:31 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_if_exist(t_cmd *cmd, char **env, char **env_path, int i)
{
	char		*command;
	char		*tmp;
	struct stat	sb;

	command = ft_strjoin(env_path[i], "/");
	tmp = command;
	command = ft_strjoin(command, cmd->cmds->content);
	free(tmp);
	tmp = command;
	cmd->cmds->content = ft_strdup(command);
	free(tmp);
	if (stat(cmd->cmds->content, &sb) == 0 && sb.st_mode & S_IXUSR)
		command_exe(cmd, env);
	else
		print_error(cmd->cmds->content, NULL, "Permission denied");
	free_table(env_path);
}

int		check_directories(t_cmd *cmd, char **env, char **env_path, int i)
{
	DIR				*rep;
	struct dirent	*read_dir;

	rep = opendir(env_path[i]);
	if (rep == NULL)
	{
		ft_putendl_fd(strerror(errno), 1);
		return (1);
	}
	while ((read_dir = readdir(rep)) != NULL)
	{
		if (ft_strcmp(read_dir->d_name, cmd->cmds->content) == 0)
		{
			execute_if_exist(cmd, env, env_path, i);
			closedir(rep);
			return (1);
		}
	}
	if (closedir(rep) == -1)
	{
		ft_putendl_fd(strerror(errno), 1);
		return (1);
	}
	return (0);
}

void	command_is_valid(t_cmd *cmd, char **env)
{
	int				i;
	char			**env_path;
	char			*tmp;

	i = 0;
	tmp = get_env_var(env, "PATH");
	env_path = ft_split(tmp, ':');
	free(tmp);
	while (env_path[i] != NULL)
	{
		if (check_directories(cmd, env, env_path, i) == 1)
		{
			return;
		}
		i++;
	}
	
	print_error(cmd->cmds->content, NULL, "command not found");
	g_error_value = 127;
	free_table(env_path);
}

void	check_if_file_executable(t_cmd *cmd, char **env)
{
	struct stat sb;
	int			fd;

	fd = open(cmd->cmds->content, O_RDONLY);
	if (fd < 0)
	{
		print_error(cmd->cmds->content, NULL, NULL);
		return ;
	}
	if (stat(cmd->cmds->content, &sb) == 0 && sb.st_mode & S_IXUSR)
		command_exe(cmd, env);
	else
		print_error(cmd->cmds->content, NULL, "Permission denied");
	close(fd);
}

char	**get_commands(t_cmd *cmd, char **env)
{
	// char	**tab;

	// if (/* function */ == 0)
	// 	ft_putendl_fd("syntax error", 1);
	// else
	// {
		// tab = // function
		env = execute_commands(cmd, env);
	// }
	return (env);
}
