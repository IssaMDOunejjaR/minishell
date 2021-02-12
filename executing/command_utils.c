/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:47:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 11:16:35 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_cmd *cmd)
{
	while (cmd->cmds != NULL)
	{
		free(cmd->cmds->content);
		free(cmd->cmds);
		cmd->cmds = cmd->cmds->next;
	}
	while (cmd->files != NULL)
	{
		free(cmd->files->file);
		free(cmd->files);
		cmd->files = cmd->files->next;
	}
}

void	free_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		check_special_carac(char *str)
{
	int		i;
	int		j;
	char	*sc;

	sc = "!#%&()*+,-./:=?@[]^{}~";
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (sc[j] != '\0')
		{
			if (str[i] == sc[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		is_all_num(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	print_error(char *command, char *content, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (command != NULL)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
	}
	if (content != NULL)
	{
		ft_putstr_fd(content, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error != NULL)
		ft_putendl_fd(error, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
}
