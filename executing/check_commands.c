/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:17:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/06 18:45:25 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_is_valid(t_cmd *cmd, char **env)
{	
	int				i;
	char			**env_path;
	DIR				*rep;
	struct	dirent	*read_dir;
	char			*command;
	char			*tmp;

	i = 0;
	tmp = get_env_var(env, "PATH");
	env_path = ft_split(tmp, ':');
	free(tmp);
	while (env_path[i] != NULL)
	{
		rep = opendir(env_path[i]);
		if (rep == NULL)
		{
			ft_putendl_fd(strerror(errno), 1);
			return ;
		}
		while ((read_dir = readdir(rep)) != NULL)
		{
			if (ft_strcmp(read_dir->d_name, cmd->cmds->content) == 0)
			{
				command = ft_strjoin(env_path[i], "/");
				tmp = command;
				command = ft_strjoin(command, cmd->cmds->content);
				free(tmp);
				tmp = command;
				cmd->cmds->content = ft_strdup(command);
				free(tmp);
				command_exe(cmd, env);
				closedir(rep);
				free_table(env_path);
				return ;
			}
		}
		if (closedir(rep) == -1)
		{
			ft_putendl_fd(strerror(errno), 1);
			return ;
		}
		i++;
	}
	ft_putendl_fd("command not found", 1);
	g_error_value = 127;
	free_table(env_path);
}

void	check_if_file_exist(t_cmd *cmd, char **env)
{
	struct stat sb;
	int			fd;
	
	fd = open(cmd->cmds->content, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd(strerror(errno), 1);
		return ;
	}
	if (stat(cmd->cmds->content, &sb) == 0 && sb.st_mode & S_IXUSR)
		command_exe(cmd, env);
	else
		ft_putendl_fd("Permission denied", 1);
	close(fd);
}

char	**check_command(t_cmd *cmd, char **env)
{
	char	*tmp;
	
	if (cmd->files != NULL)
		check_files(cmd);
	if (cmd->cmds == NULL)
		return (env);
	tmp = cmd->cmds->content;
	if (tmp[0] == '.' || tmp[0] == '/')
		check_if_file_exist(cmd, env);
	else if (ft_strcmp(tmp, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(tmp, "pwd") == 0)
		print_pwd();
	else if (ft_strcmp(tmp, "env") == 0)
		ft_env(cmd, env);
	else if (ft_strcmp(tmp, "export") == 0)
		print_export(env);
	else
		command_is_valid(cmd, env);
	return (env);
}

int		check_built_in(t_cmd *cmd)
{
	if (cmd->cmds == NULL)
		return (1);
	if (ft_strcmp(cmd->cmds->content, "cd") == 0 || 
	(ft_strcmp(cmd->cmds->content, "export") == 0 
	&& ft_lstsize(cmd->cmds) > 1) || 
	ft_strcmp(cmd->cmds->content, "unset") == 0 || 
	ft_strcmp(cmd->cmds->content, "exit") == 0)
		return (1);
	return (0);
}

char	**exec_built_in(t_cmd *cmd, char **env)
{
	if (cmd->files != NULL)
		check_files(cmd);
	if (cmd->cmds == NULL)
		return (env);
	if (ft_strcmp(cmd->cmds->content, "cd") == 0)
		env = change_directory(cmd, env);
	else if (ft_strcmp(cmd->cmds->content, "export") == 0)
		env = ft_export(cmd, env);
	else if (ft_strcmp(cmd->cmds->content, "unset") == 0)
		env = ft_unset(cmd, env);
	else if (ft_strcmp(cmd->cmds->content, "exit") == 0)
		exit_shell(cmd, env);
	return (env);	
}

int		set_commands(t_cmd *cmd)
{
	if (test == 1)
		return (2);
	if (test == 0)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("hello")));
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("-la")));
		
		// lst_file_add_back(&cmd->files, lst_file_new(ft_strdup("to_do.txt"), READ));
		// cmd->type = PIPE;
	}
	else if (test == 1)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("grep")));
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("OLDPWD")));
	}
	else if (test == 2)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("cd")));
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("..")));
	}
	else if (test == 3)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("env")));
		cmd->type = PIPE;
	}
	else if (test == 4)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("grep")));
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("OLDPWD")));
	}
	test++;
	return (1);
}

char	**execute_commands(t_cmd *cmd, char **env)
{
	int		pipe_fd[2];
	int		fd;
	pid_t	id;
	int		status;

	fd = 0;
	test = 0;
	while (set_commands(cmd) != 2)
	{
		if (check_built_in(cmd) && cmd->type != PIPE)
			env = exec_built_in(cmd, env);
		else
		{
			if (pipe(pipe_fd) == -1)
				ft_putendl_fd(strerror(errno), 1);
			if ((id = fork()) == -1)
				ft_putendl_fd(strerror(errno), 1);
			else if (id == 0)
			{
				if (dup2(fd, 0) == -1)
					ft_putendl_fd(strerror(errno), 1);
				if (cmd->type == PIPE && cmd->files == NULL)
				{
					close(pipe_fd[0]);
					if (dup2(pipe_fd[1], 1) == -1)
						ft_putendl_fd(strerror(errno), 1);
				}
				check_command(cmd, env);
				exit(g_error_value);
			}
			else
			{
				waitpid(id, &status, 0);
				if (cmd->type == PIPE && cmd->files == NULL)
				{
					close(pipe_fd[1]);
					fd = pipe_fd[0];
				}
				if (WIFEXITED(status))
					g_error_value = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
				{
					if (WTERMSIG(status) == 2)
						g_error_value = 130;
					if (WTERMSIG(status) == 3)
						g_error_value = 131;
				}
			}
		}
		free_commands(cmd);
		cmd->type = END;
	}
	return (env);
}

char	**get_commands(t_cmd *cmd, char **env)
{
	// int		ret;

	// while ((ret = /* (parse function)*/) != 2)
	// {
	// 	if (ret == 0)
	// 	{
	// 		ft_putendl_fd("syntax error", 1);
	// 		free_commands(cmd);
	// 		return (env);
	// 	}
	// 	free_commands(cmd);
	// }

	env = execute_commands(cmd, env);
	return (env);
}