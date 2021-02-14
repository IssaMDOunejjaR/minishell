/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:18:21 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/14 11:05:11 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_file		*handle_write_append(t_cmd *cmd)
{
	int		fd;
	t_file	*file;
	t_file	*tmp;

	file = NULL;
	tmp = cmd->files;
	while (cmd->files != NULL)
	{
		if (cmd->files->type == WRITE || cmd->files->type == APPEND)
		{
			fd = open(cmd->files->file, O_CREAT, 0666);
			file = cmd->files;
			close(fd);
		}
		cmd->files = cmd->files->next;
	}
	cmd->files = tmp;
	return (file);
}

static	t_file		*handle_read(t_cmd *cmd)
{
	int		fd;
	t_file	*file;
	t_file	*tmp;

	file = NULL;
	tmp = cmd->files;
	while (cmd->files != NULL)
	{
		if (cmd->files->type == READ)
		{
			fd = open(cmd->files->file, O_RDONLY, 0666);
			file = cmd->files;
			close(fd);
		}
		cmd->files = cmd->files->next;
	}
	cmd->files = tmp;
	return (file);
}

static	int			check_write_append(t_cmd *cmd, t_file *write)
{
	int		fd;
	int		option;

	option = write->type == APPEND ? O_APPEND | O_RDWR : O_RDWR;
	fd = open(write->file, option, 0666);
	if (fd < 0)
	{
		print_error(cmd->cmds->content, write->file, NULL);
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int					create_and_check(t_cmd *cmd)
{
	int		fd;
	t_file	*tmp;

	tmp = cmd->files;
	fd = 0;
	while (cmd->files != NULL)
	{
		if ((fd = get_write_append_read(cmd)) < 0)
		{
			cmd->files = tmp;
			return (1);
		}
		if (fd != 0)
			close(fd);
		cmd->files = cmd->files->next;
	}
	cmd->files = tmp;
	return (0);
}

int					check_files(t_cmd *cmd)
{
	t_file	*write;
	t_file	*read;
	int		fd;

	if (create_and_check(cmd) == 1)
		return (1);
	if (cmd->cmds == NULL)
		return (1);
	read = handle_read(cmd);
	if (read != NULL)
	{
		fd = open(read->file, O_RDONLY, 0666);
		if (fd < 0)
		{
			print_error(cmd->cmds->content, read->file, NULL);
			return (1);
		}
		dup2(fd, 0);
		close(fd);
	}
	write = handle_write_append(cmd);
	if (write != NULL)
		if (check_write_append(cmd, write) == 1)
			return (1);
	return (0);
}
