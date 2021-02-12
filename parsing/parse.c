/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:21:27 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/11 18:58:05 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r' || line[i] == '\n'  || line[i] == '\f' || line[i] == '\v')
		i++;
	// printf("i'm skipping spaces\n");
	return (i);
}

void	init_cmd(t_cmd *cmd)
{
	// cmd = malloc(sizeof(t_cmd));
	// cmd->cmds = ft_lstnew(NULL);
	// cmd = malloc(sizeof(t_cmd));
	cmd->files = NULL;
	cmd->cmds = NULL;
	// cmd->files->type = END;
	// cmd->files->file = NULL;
	cmd->type = END;
}

int		check_line(char *line)
{
	int		i;
	char	type;
	int		check;

	i = 0;
	i = skip_spaces(line, i);
	if (is_charm(line[i]) == 1)
		return (1);
	while (line[i])
	{
		check = 0;
		if (line[i] == '\'' || line[i] == '"')
		{
			type = line[i];
			i++;
			while (line[i])
			{
				if ((line[i] == type && type == '"' && line[i - 1] != '\\') || (line[i] == type && type == '\''))//(line[i] == type && type == '"' && line[i - 1] != '\\') || (line[i] == type && type == '\'')
				{
					check++;
					i++;
					break;
				}///////test
				if (line[i])
					i++;
			}
			if (check == 0)
				return (1);
		}
		else if (line[i] == '|')
		{
			// printf ("ok\n");
			if (check_pipe(line, i) == 0)
				return (1);
			else
				i = check_pipe(line, i);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			if (check_app(line, i) == 0)
				return (1);
			else
				i = check_app(line, i);
		}
		else if (line[i] == ';')
		{
			if (check_semi(line, i) == 0)
				return (1);
			else
				i = check_semi(line, i);	
		}
		else
			i++;
	}
	return (0);
}

int		get_command(char **env, t_cmd *cmd, char **tab2) //echo "hello $USER test allah"
{
	int		i;
	int		q;
	int		j;

	i = 1;
	init_cmd(cmd);
	while (tab2[g_t])
	{
		if (check_end_cmd(cmd, tab2, env) == 1)
		{
			return (1);
		}
		else if (tab2[g_t] && (ft_strcmp(tab2[g_t], ">") && ft_strcmp(tab2[g_t], "<") && ft_strcmp(tab2[g_t], ">>")))
			handle_cmd(tab2[g_t++], env, cmd);
		// else if (check_end_cmd(cmd, tab2, env) == 0)
		// 	;
		// printf("tab = |%s|\n", tab2[g_t]);
	}
	return (2);
}

/*
	t_list *head;

	head = NULL;
	lstaddback(&head, lstnew("echo"));
*/