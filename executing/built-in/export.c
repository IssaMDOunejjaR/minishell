/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:55:03 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/10 12:02:11 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*add_quotes(char *str)
{
	char	*new;
	char	**tmp;
	char	*tmp1;

	tmp = ft_split(str, '=');
	if (table_len_2d(tmp) != 2)
	{
		free_table(tmp);
		return (ft_strjoin("declare -x ", str));
	}
	new = ft_strjoin("\"", tmp[1]);
	tmp1 = new;
	new = ft_strjoin(new, "\"");
	free(tmp1);
	tmp1 = new;
	new = ft_strjoin("=", new);
	free(tmp1);
	tmp1 = new;
	new = ft_strjoin(tmp[0], new);
	free(tmp1);
	tmp1 = new;
	new = ft_strjoin("declare -x ", new);
	free(tmp1);
	free_table(tmp);
	return (new);
}

static	char	**convert_env(char **env)
{
	int		i;
	char	**new;
	char	**tmp;
	char	*tmp2;

	new = malloc(sizeof(char*) * (table_len_2d(env) + 1));
	tmp = sort_table_2d(env);
	i = 0;
	while (tmp[i] != NULL)
	{
		tmp2 = add_quotes(tmp[i]);
		new[i] = ft_strdup(tmp2);
		free(tmp2);
		i++;
	}
	new[i] = NULL;
	free_table(tmp);
	return (new);
}

void			print_export(char **env)
{
	int		i;
	char	**new_env;

	new_env = convert_env(env);
	i = 0;
	while (new_env[i] != NULL)
	{
		ft_putendl_fd(new_env[i], 1);
		i++;
	}
	free_table(new_env);
}

char			**ft_export(t_cmd *cmd, char **env)
{
	t_list	*tmp;

	tmp = cmd->cmds;
	cmd->cmds = cmd->cmds->next;
	if (g_prev_type != PIPE)
	{
		while (cmd->cmds != NULL)
		{
			if (find_env_var(env, cmd->cmds->content) == 1)
				env = change_env_var(cmd->cmds->content, env);
			else
				env = tab_join(env, cmd->cmds->content);
			cmd->cmds = cmd->cmds->next;
		}
	}
	cmd->cmds = tmp;
	return (env);
}
