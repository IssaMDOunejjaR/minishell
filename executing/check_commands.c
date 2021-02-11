/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:17:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/01 17:10:10 by ychennaf         ###   ########.fr       */
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
		{
			free_table(tmp);
			break ;
		}
		free_table(tmp);
		i++;
	}
	return (ft_split(tmp[1], ':'));
}

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
	ft_strcmp(tmp, "unset") == 0)
		printf("is a built in command\n");
	else if (ft_strcmp(tmp, "cd") == 0)
		change_directory(cmd);
	else if (ft_strcmp(tmp, "pwd") == 0)
		ft_putendl_fd(getcwd(NULL, 0), 1);
	else if (ft_strcmp(tmp, "env") == 0)
		print_env(env);
	else if (ft_strcmp(tmp, "exit") == 0)
		exit_shell();
	else
		command_is_valid(cmd, env);
}

void	get_commands(t_cmd *cmd, char **env)
{
	// int ret;

	// while (/* (parse function) != 0 */1)
	// {
		check_command(cmd, env);
	// }
	// if (ret == 0)
	// 	ft_putstr_fd("syntax error!", 1);
}