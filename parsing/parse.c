/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:21:27 by ychennaf          #+#    #+#             */
/*   Updated: 2021/01/27 15:11:54 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_spaces(char *line)
{
	while(line[g_i] == ' ')
		g_i++;
	printf("i'm skipping spaces\n");
}

static void	init_cmd(t_cmd *cmd)
{
	// cmd = malloc(sizeof(t_cmd));
	// cmd->cmds = ft_lstnew(NULL);
	cmd = malloc(sizeof(t_cmd));
	cmd->files = malloc(sizeof(t_file));
	cmd->cmds = NULL;
	cmd->files->type = END;
	cmd->files->file = NULL;
	cmd->type = END;
}

static	int	handle_quotes(char **env, t_cmd *cmd, char type, char *line)
{
	int		end;
	int		i;
	char	*tmp;
	char	*ret_env;
	
	end = 0;
	tmp = "";
	g_i++;
	i = 0;
	while (line[g_i + 1] != '\0' || line [g_i] == type)
	{
		if (line[g_i] == type)
		{
			end = 1;
			break;
		}
		else if (line[g_i] == '$' && type == '\"')
		{
			tmp = ft_strjoin(tmp, ft_substr(line, g_i - i, i));
			ret_env = get_env(env,line);//environ //ret_env uselesssssssssssssssssss
			tmp = ft_strjoin(tmp, ret_env);
			printf("%c --> g_i = %d\n",line[g_i],g_i);
			printf("tmp = %s\n", tmp);
			i = 0;
			if (line[g_i] == type)
				ft_lstadd_back(&cmd->cmds, ft_lstnew(tmp));
		}
		i++;
		g_i++;
	}
	if (end == 0)
		return(1);
	else
	{
		tmp = ft_strjoin(tmp, ft_substr(line, g_i - i, i));
		// printf("i'm here %c\n", line[g_i]);
		// tmp = ft_substr(line, g_i - i, i); // free(tmp);
		ft_lstadd_back(&cmd->cmds, ft_lstnew(tmp));
	}
	printf("tmp else = %s\n",tmp);
	return (0);
}

int		get_command(char *line, char **env, t_cmd *cmd) //echo "hello $USER test allah"
{
	// char	*tmp;
	// int		i;
	int		q;

	init_cmd(cmd);
	// i = g_i;
	while(line[g_i] != '\0')
	{
		// printf("g_i = %d\n", g_i);
		q = 0;
		if (line[g_i] == ' ')
			skip_spaces(line);
		else if (line[g_i] == '|')
		{
			cmd->type = PIPE;
			g_i++;
			break;
		}
		else if (line[g_i] == ';')
		{
			cmd->type = END;
			g_i++;
			break;
		}
		else if (line[g_i] == '$')
			ft_lstadd_back(&cmd->cmds, ft_lstnew(get_env(env, line)));
		else if (line[g_i] == '\'' || line[g_i] == '\"')
			q = handle_quotes(env, cmd, line[g_i], line);
		else
		{
			ft_lstadd_back(&cmd->cmds, ft_lstnew(get_simple_s(line)));
		}
		if (q == 1)
			printf("multiple command line\n");
		g_i++;
	}
	while(cmd->cmds != NULL)
	{
		printf("cmds = %s\n", cmd->cmds->content);
		cmd->cmds = cmd->cmds->next;
	}
	// tmp = ft_substr(line, i, g_i - i);
	return (2);
}

/*
	t_list *head;

	head = NULL;
	lstaddback(&head, lstnew("echo"));
*/