/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:17:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/19 12:25:48 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*execute_if_exist(t_cmd *cmd, char **env_path, int i)
{
	char		*command;
	char		*tmp;

	command = ft_strjoin(env_path[i], "/");
	tmp = command;
	command = ft_strjoin(command, cmd->cmds->content);
	free(tmp);
	return (command);
}

char	*check_directories(t_cmd *cmd, char **env_path, int i)
{
	DIR				*rep;
	struct dirent	*read_dir;
	char			*tmp;

	tmp = NULL;
	rep = opendir(env_path[i]);
	if (rep != NULL)
	{
		while ((read_dir = readdir(rep)) != NULL)
		{
			if (ft_strcmp(read_dir->d_name, cmd->cmds->content) == 0)
				tmp = execute_if_exist(cmd, env_path, i);
		}
		closedir(rep);
	}
	return (tmp);
}

void	command_is_valid(t_cmd *cmd)
{
	int				i;
	char			**env_path;
	char			*tmp;
	char			*tmp2;

	i = 0;
	tmp = get_var_env("PATH");
	env_path = ft_split(tmp, ':');
	free(tmp);
	while (env_path[i] != NULL)
	{
		if ((tmp = check_directories(cmd, env_path, i)) != NULL)
			tmp2 = tmp;
		i++;
	}
	if (final_exec(cmd, tmp2) == 0)
	{
		print_error(cmd->cmds->content, NULL, "command not found");
		g_error_value = 127;
	}
	free_table(env_path);
}

void	check_if_file_executable(t_cmd *cmd)
{
	struct stat sb;
	int			fd;

	fd = open(cmd->cmds->content, O_RDONLY);
	if (fd < 0)
	{
		print_error(cmd->cmds->content, NULL, NULL);
		return ;
	}
	close(fd);
	if (stat(cmd->cmds->content, &sb) == 0 && sb.st_mode & S_IXUSR)
		command_exe(cmd, cmd->cmds->content);
	else
		print_error(cmd->cmds->content, NULL, "Permission denied");
}

void	get_commands(t_cmd *cmd, char *line)
{
	char	**tab;

	if (check_line(line) == 1)
		print_error(NULL, NULL, "syntax error");
	else
	{
		tab = fill_tab2(line);
		execute_commands(cmd, tab);
		free_table(tab);
		g_check = 0;
	}
}
