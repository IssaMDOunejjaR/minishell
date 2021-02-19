/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 10:58:33 by iounejja          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2021/02/17 14:33:50 by ychennaf         ###   ########.fr       */
=======
/*   Updated: 2021/02/18 16:30:22 by iounejja         ###   ########.fr       */
>>>>>>> 3bbd984... fix a lot of things
=======
/*   Updated: 2021/02/19 12:02:22 by iounejja         ###   ########.fr       */
>>>>>>> 22fb315... minishell
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_args(t_cmd *cmd)
{
	int		i;
	char	**args;
	t_list	*tmp;

	tmp = cmd->cmds;
	args = malloc(sizeof(char*) * (ft_lstsize(cmd->cmds) + 1));
	i = 0;
	while (cmd->cmds != NULL)
	{
		args[i] = ft_strdup(cmd->cmds->content);
		cmd->cmds = cmd->cmds->next;
		i++;
	}
	args[i] = NULL;
	cmd->cmds = tmp;
	return (args);
}

char	**init_global(void)
{
	int		shell_lvl;
	char	*new_shellvl;
	char	*tmp;

	g_error_value = 0;
	g_latest_cmd = ft_strdup("minishell");
	g_old_pwd = ft_strdup("");
	g_env = change_env_var("OLDPWD");
	tmp = get_env_var("SHLVL");
	shell_lvl = ft_atoi(tmp) + 1;
	free(tmp);
	tmp = ft_itoa(shell_lvl);
	new_shellvl = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	g_env = change_env_var(new_shellvl);
	free(new_shellvl);
	return (g_env);
}

void	get_latest_cmd(t_cmd *cmd)
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

char	**split_export(char *str, char **tmp)
{
	int		i;
	int		j;
	int		check;

	i = 0;
	check = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			check = 1;
			break ;
		}
		i++;
	}
	j = 0;
	if (check == 1)
		tmp = malloc(sizeof(char*) * 3);
	else
		tmp = malloc(sizeof(char*) * 2);
	tmp[j++] = ft_substr(str, 0, i);
	if (check == 1)
		tmp[j++] = ft_substr(str, i + 1, ft_strlen(str));
	tmp[j] = NULL;
	return (tmp);
}
