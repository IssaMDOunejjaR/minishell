/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:57:31 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 15:25:05 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_commands(t_cmd *cmd)
{
	if (test == 1)
		return (2);
	if (test == 0)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("cat")));
		// ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("ttttt")));
		// ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("/dev/random")));
		
		// lst_file_add_back(&cmd->files, lst_file_new(ft_strdup("t1"), WRITE));
		// lst_file_add_back(&cmd->files, lst_file_new(ft_strdup("dfgsdfgsdf"), READ));
		// lst_file_add_back(&cmd->files, lst_file_new(ft_strdup("t2"), WRITE));
		cmd->type = END;
	}
	else if (test == 1)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("cat")));
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("ttt")));
		// ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("@")));
		// ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("head")));
		// ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("-c")));
		// ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("100")));

		// lst_file_add_back(&cmd->files, lst_file_new(ft_strdup("t1"), WRITE));
		cmd->type = END;
	}
	else if (test == 2)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("env")));
		// cmd->type = PIPE;
	}
	else if (test == 3)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("grep")));
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("env")));
		// ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("exe")));
		cmd->type = PIPE;
	}
	else if (test == 4)
	{
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("tr")));
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("_")));
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("|")));
	}
	test++;
	return (1);
}

static	int		parent_process(t_cmd *cmd, pid_t id, int pipe_fd[2])
{
	int status;
	int	fd;

	fd = 0;
	if (cmd->type == END)
	{
		waitpid(id, &status, 0);
		while (waitpid(0, 0, 0) == 0)
			;	
	}
	if (cmd->type != PIPE)
		close(pipe_fd[0]);
	if (cmd->type == PIPE)
		fd = pipe_fd[0];
	if (WIFEXITED(status))
		g_error_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		g_error_value = 130;
	else if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
		g_error_value = 131;
	if (g_prev_fd_read == -1)
		g_prev_fd_read = fd;
	else
	{
		if (g_prev_fd_read != 0)
			close(g_prev_fd_read);
		g_prev_fd_read = fd;
	}
	return (fd);
}

static	void	child_process(t_cmd *cmd, char **env, int fd, int pipe_fd[2])
{
	if (dup2(fd, 0) == -1)
		ft_putendl_fd(strerror(errno), 1);
	if (cmd->type == PIPE && cmd->files == NULL)
	{
		if (dup2(pipe_fd[1], 1) == -1)
			ft_putendl_fd(strerror(errno), 1);
	}
	check_command(cmd, env);
}

static	int		execute_proccess(t_cmd *cmd, char **env, int fd, int pipe_fd[2])
{
	pid_t	id;

	if (pipe(pipe_fd) == -1)
		ft_putendl_fd(strerror(errno), 1);
	if ((id = fork()) == -1)
		ft_putendl_fd(strerror(errno), 1);
	else if (id == 0)
	{
		child_process(cmd, env, fd, pipe_fd);
		exit(g_error_value);
	}
	else
	{
		close(pipe_fd[1]);
		fd = parent_process(cmd, id, pipe_fd);
	}
	return (fd);
}

char			**init_global(char **env)
{
	int		shell_lvl;
	char	*new_shellvl;
	char	*tmp;
	
	g_error_value = 0;
	g_latest_cmd = ft_strdup("minishell");
	g_old_pwd = ft_strdup("");
	env = change_env_var("OLDPWD", env);
	tmp = get_env_var(env, "SHLVL");
	shell_lvl = ft_atoi(tmp) + 1;
	free(tmp);
	tmp = ft_itoa(shell_lvl);
	new_shellvl = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	env = change_env_var(new_shellvl, env);
	free(new_shellvl);
	return (env);
}

void			get_latest_cmd(t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->cmds;
	while (cmd->cmds->next != NULL)
		cmd->cmds = cmd->cmds->next;
	if (cmd->type != PIPE && g_prev_type != PIPE)
	{
		free(g_latest_cmd);
		g_latest_cmd = ft_strdup(cmd->cmds->content);
	}
	else
	{
		free(g_latest_cmd);
		g_latest_cmd = ft_strdup("");
	}
	cmd->cmds = tmp;
}

char			**execute_commands(t_cmd *cmd, char **env)
{
	int		pipe_fd[2];
	int		fd;

	test = 0;
	g_prev_fd_read = -1;
	fd = 0;
	g_prev_type = END;
	while (set_commands(cmd) != 2)
	{
		cmd->cmds = check_more_args(cmd);
		if (check_built_in(cmd))
			env = exec_built_in(cmd, env);
		else
			fd = execute_proccess(cmd, env, fd, pipe_fd);
		get_latest_cmd(cmd);
		free_commands(cmd);
		g_prev_type = cmd->type;
		cmd->type = END;
	}
	return (env);
}
