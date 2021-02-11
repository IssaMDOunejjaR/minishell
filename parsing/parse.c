/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:21:27 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/11 17:10:54 by ychennaf         ###   ########.fr       */
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
					printf("|%d|\n",i);
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

int		get_command(char *line, char **env, t_cmd *cmd, char **tab2) //echo "hello $USER test allah"
{
	// char	*tmp;
	int		i;
	int		q;
	int		j;

	i = 1;
	init_cmd(cmd);
	// if (check_line(line) == 1)
	// 	return (0);
	// tab2 = fill_tab2(line);
	// printf("i = |%d|\n", i);
	// printf("l = |%d|\n" ,size_q(line, env, &i, '\''));
	// printf("i = |%d|\n", i);
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
	// printf("khrej\n");
	// cmd = NULL;
	// i = g_i;
	// while(line[g_i] != '\0')
	// {
	// 	// printf("g_i = %d\n", g_i);
	// 	q = 0;
	// 	if (line[g_i] == ' ')
	// 		g_i += skip_spaces(line, g_i);
	// 	if (line[g_i] == '|')
	// 	{
	// 		cmd->type = PIPE;
	// 		g_i++;
	// 		break;
	// 	}
	// 	else if (line[g_i] == ';')
	// 	{
	// 		cmd->type = END;
	// 		g_i++;
	// 		break;
	// 	}
	// 	else if (line[g_i] != ' ')
	// 		q = get_simple_s(line, cmd, env); //add_lsdoll(env, line, cmd); //ATTENTION $$$$$$$
	// 	// else if (line[g_i] == '\'' || line[g_i] == '\"')
	// 	// 	q = get_simple_s(line, cmd, env);
	// 	// else
	// 	// 	 q = get_simple_s(line, cmd, env);
	// 	if (q == 1)
	// 		printf("multiple command line\n");
	// 	g_i++;
		
	// }
	// // ft_putendl_fd("OK",1);
	// // cmd = NULL;
	// t_list *test;
	// t_file *tmp;

	// test = cmd->cmds;
	// while(cmd->cmds != NULL)
	// {
	// 	// printf("cmds = %s\n", cmd->cmds->content);
	// 	ft_putstr_fd("|",1);
	// 	ft_putstr_fd(cmd->cmds->content,1);
	// 	ft_putendl_fd("|",1);
	// 	cmd->cmds = cmd->cmds->next;
	// }
	// cmd->cmds = test;
	// tmp = cmd->files;
	// while(cmd->files != NULL)
	// {
	// 	ft_putstr_fd("file \n|",1);
	// 	ft_putstr_fd(cmd->files->file,1);
	// 	ft_putstr_fd("| -- ",1);
	// 	ft_putendl_fd(ft_itoa(cmd->files->type),1);
	// 	cmd->files = cmd->files->next;
	// }
	// cmd->files = tmp;
	// free_commands(cmd);
	// tmp = ft_substr(line, i, g_i - i);
	return (2);
}

/*
	t_list *head;

	head = NULL;
	lstaddback(&head, lstnew("echo"));
*/