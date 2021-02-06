/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:18:21 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/06 11:00:56 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_file	*handle_write_append(t_cmd *cmd)
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

static	t_file	*handle_read(t_cmd *cmd)
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
			if (fd < 0)
			{
				ft_putendl_fd(strerror(errno), 1);
				return (file);
			}
			close(fd);
		}
		cmd->files = cmd->files->next;
	}
	cmd->files = tmp;
	return (file);
}

void		check_files(t_cmd *cmd)
{
	t_file	*write;
	t_file	*read;
	int		fd;
	int		option;
	
	write = handle_write_append(cmd);
	read = handle_read(cmd);
	if (write != NULL)
	{
		option = write->type == APPEND ? O_APPEND | O_RDWR : O_RDWR;
		fd = open(write->file, option, 0666);
		if (dup2(fd, 1) == -1)
			ft_putendl_fd(strerror(errno), 1);
		close(fd);
	}
	if (read != NULL)
	{
		fd = open(read->file, O_RDONLY, 0666);
		if (dup2(fd, 0) == -1)
			ft_putendl_fd(strerror(errno), 1);
		close(fd);
	}
}