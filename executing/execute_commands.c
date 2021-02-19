/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:57:31 by iounejja          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/02/17 15:32:23 by ychennaf         ###   ########.fr       */
=======
/*   Updated: 2021/02/18 17:37:58 by iounejja         ###   ########.fr       */
>>>>>>> 3bbd984... fix a lot of things
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	save_pipe_fd(int fd)
{
	if (g_prev_fd_read == -1)
		g_prev_fd_read = fd;
	else
	{
		if (g_prev_fd_read != 0)
			close(g_prev_fd_read);
		g_prev_fd_read = fd;
	}
}

static	int		parent_process(t_cmd *cmd, pid_t id, int pipe_fd[2])
{
	int status;
	int	fd;

	fd = 0;
	if (cmd->type == END)
	{
		close(pipe_fd[0]);
		waitpid(id, &status, 0);
		signal_process(status);
	}
	if (cmd->type != PIPE)
		close(pipe_fd[0]);
	if (cmd->type == PIPE)
		fd = pipe_fd[0];
	save_pipe_fd(fd);
	return (fd);
}

static	void	child_process(t_cmd *cmd, int fd, int pipe_fd[2])
{
	if (dup2(fd, 0) == -1)
		ft_putendl_fd(strerror(errno), 1);
	if (cmd->type == PIPE)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1)
			ft_putendl_fd(strerror(errno), 1);
	}
	check_command(cmd);
}

static	int		execute_proccess(t_cmd *cmd, int fd, int pipe_fd[2])
{
	pid_t	id;

	if (pipe(pipe_fd) == -1)
		ft_putendl_fd(strerror(errno), 1);
	if ((id = fork()) == -1)
		ft_putendl_fd(strerror(errno), 1);
	else if (id == 0)
	{
		child_process(cmd, fd, pipe_fd);
		exit(g_error_value);
	}
	else
	{
		close(pipe_fd[1]);
		fd = parent_process(cmd, id, pipe_fd);
	}
	return (fd);
}

void			execute_commands(t_cmd *cmd, char **tab)
{
	int		pipe_fd[2];
	int		fd;
	int		ret;

	fd = 0;
	init_exec();
	while ((ret = get_command(cmd, tab)))
	{
		g_check = 1;
		save_pwd();
		if (check_built_in(cmd))
			exec_built_in(cmd);
		else
			fd = execute_proccess(cmd, fd, pipe_fd);
		if (cmd->cmds != NULL)
			get_latest_cmd(cmd);
		free_commands(cmd);
		g_prev_type = cmd->type;
		if (ret == 2)
			break ;
	}
<<<<<<< HEAD
	while (waitpid(0, 0, 0) > 0)
=======
	while (waitpid(0, 0, 0) >= 0)
>>>>>>> 3bbd984... fix a lot of things
		;
}
