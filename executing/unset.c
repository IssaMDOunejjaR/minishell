/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:33:16 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/10 12:02:11 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**delete_env_var(char **env, char *env_var)
{
	int		i;
	int		j;
	char	**new_env;
	char	**tmp;
	char	**var;

	i = 0;
	j = 0;
	var = ft_split(env_var, '=');
	new_env = malloc(sizeof(char*) * (table_len_2d(env)));
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
		if (ft_strcmp(tmp[0], var[0]) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		free_table(tmp);
		i++;
	}
	new_env[j] = NULL;
	free_table(var);
	return (new_env);
}

char	**ft_unset(t_cmd *cmd, char **env)
{
	char	**tmp;
	t_list	*tmp_lst;

	tmp_lst = cmd->cmds;
	cmd->cmds = cmd->cmds->next;
	while (cmd->cmds != NULL)
	{
		if (check_special_carac(cmd->cmds->content) == 1)
		{
			print_error("unset", cmd->cmds->content, "not a valid identifier");
			cmd->cmds = tmp_lst;
			return (env);
		}
		if (find_env_var(env, cmd->cmds->content) == 1 &&
		cmd->type != PIPE && g_prev_type != PIPE)
		{
			tmp = env;
			env = delete_env_var(env, cmd->cmds->content);
			free_table(tmp);
		}
		cmd->cmds = cmd->cmds->next;
	}
	cmd->cmds = tmp_lst;
	return (env);
}
