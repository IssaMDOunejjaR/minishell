/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:47:54 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/19 11:39:06 by iounejja         ###   ########.fr       */
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

int		export_check_more(char tmp, char *sc)
{
	int i;

	i = 0;
	while (sc[i] != '\0')
	{
		if (tmp == sc[i])
			return (1);
		i++;
	}
	return (0);
}

int		export_check_special_carac(char *str)
{
	int		i;
	char	*sc;
	char	**tmp;

	tmp = ft_split(str, '=');
	if (tmp[0] == NULL)
	{
		free_table(tmp);
		return (1);
	}
	sc = "!#%&()*+,-./:?@[]^{}~";
	i = 0;
	while (tmp[0][i] != '\0')
	{
		if (export_check_more(tmp[0][i], sc) == 1 || ft_isdigit(tmp[0][0]))
		{
			free_table(tmp);
			return (1);
		}
		i++;
	}
	free_table(tmp);
	return (0);
}

int		unset_check_special_carac(char *str)
{
	int		i;
	int		j;
	char	*sc;

	sc = "!#%&()*+,-./:=?@[]^{}~";
	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
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
