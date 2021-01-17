/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:17:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/17 18:13:30 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		**get_env_path(char **env)
{
	int		i;
	char	**tmp;
	
	i = 0;
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
		if (ft_strcmp(tmp[0], "PATH") == 0)
			break ;
		free_table(tmp);
		i++;
	}
	return (ft_split(tmp[1], ':'));
}

static void		command_is_valid(t_cmd *cmd, char **env)
{	
	int				i;
	char			**env_path;
	DIR				*rep;
	struct	dirent	*read_dir;
	int				cmd_found;

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

static void		check_if_file_exist(t_cmd *cmd)
{
	struct stat sb;

	if (open(cmd->cmds->content, O_RDONLY) < 0)
	{
		ft_putendl_fd(strerror(errno), 1);
		return ;
	}
	if (stat(cmd->cmds->content, &sb) == 0 && sb.st_mode & S_IXUSR)
		printf("executable\n");
	else
		printf("not executable\n");
}

void			check_command(t_cmd *cmd, char **env)
{
	char *tmp;

	tmp = cmd->cmds->content;
	if (tmp[0] == '.' || tmp[0] == '/')
		check_if_file_exist(cmd);
	else if (ft_strcmp(tmp, "echo") == 0 || ft_strcmp(tmp, "export") == 0 || 
	ft_strcmp(tmp, "unset") == 0 || ft_strcmp(tmp, "exit") == 0)
		printf("is a built in command\n");
	else if (ft_strcmp(tmp, "cd") == 0)
		change_directory(cmd);
	else if (ft_strcmp(tmp, "pwd") == 0)
		print_cwd();
	else if (ft_strcmp(tmp, "env") == 0)
		print_env(env);
	else
		command_is_valid(cmd, env);
}