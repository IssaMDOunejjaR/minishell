/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:55:03 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 17:06:12 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*join_export(char **tmp)
{
	char	*new;
	char	*tmp1;

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
	return (new);
}

static	char	*add_quotes(char *str)
{
	char	*new;
	char	**tmp;

	tmp = NULL;
	tmp = split_export(str, tmp);
	if (table_len_2d(tmp) != 2)
	{
		free_table(tmp);
		return (ft_strjoin("declare -x ", str));
	}
	new = join_export(tmp);
	free_table(tmp);
	return (new);
}

char			**convert_env(void)
{
	int		i;
	char	**new;
	char	**tmp;
	char	*tmp2;

	new = malloc(sizeof(char*) * (table_len_2d(g_env) + 1));
	tmp = sort_table_2d(g_env);
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

static	void	export_var(t_cmd *cmd)
{
	if (find_env_var(cmd->cmds->content) == 1)
		g_env = change_env_var(cmd->cmds->content);
	else
		g_env = tab_join(g_env, cmd->cmds->content);
}

void			ft_export(t_cmd *cmd)
{
	t_list	*tmp;

	g_error_value = 0;
	tmp = cmd->cmds;
	if (ft_lstsize(cmd->cmds) == 1)
		print_export();
	else
	{
		cmd->cmds = cmd->cmds->next;
		while (cmd->cmds != NULL)
		{
			if (export_check_special_carac(cmd->cmds->content) == 1)
			{
				print_error("export", cmd->cmds->content,
				"not a valid identifier");
				cmd->cmds = cmd->cmds->next;
				continue ;
			}
			if (g_prev_type != PIPE && cmd->type != PIPE)
				export_var(cmd);
			cmd->cmds = cmd->cmds->next;
		}
	}
	cmd->cmds = tmp;
}
