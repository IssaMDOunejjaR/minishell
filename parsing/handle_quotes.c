/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:19:05 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/04 17:25:16 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// int	handle_quotes(char **env, t_cmd *cmd, char type, char *line)
// {
// 	int		end;
// 	int		i;
// 	char	*tmp;
// 	char	*ret_env;

	
// 	end = 0;
// 	tmp = "";
// 	g_i++;
// 	i = 0;
// 	while (line[g_i] != '\0' || line [g_i] == type)
// 	{
// 		if (line[g_i] == type)
// 		{
// 			end = 1;
// 			break;
// 		}
// 		else if (line[g_i] == '$' && type == '\"')
// 		{
// 			tmp = ft_strjoin(tmp, ft_substr(line, g_i - i, i));
// 			ret_env = get_env(env,line);//environ //ret_env uselesssssssssssssssssss
// 			tmp = ft_strjoin(tmp, ret_env);
// 			// printf("%c --> g_i = %d\n",line[g_i],g_i);
// 			printf("tmp = %s\n", tmp);
// 			i = 0;
// 			// if (line[g_i] == type)
// 			// 	ft_lstadd_back(&cmd->cmds, ft_lstnew(tmp));
// 			// if (line [g_i] == type)
// 			// 	end = 1;
// 		}
// 		i++;
// 		g_i++;
// 	}
// 	if (end == 0)
// 		return(1);
// 	else
// 	{
// 		tmp = ft_strjoin(tmp, ft_substr(line, g_i - i, i));
// 		// printf("i'm here %c\n", line[g_i]);
// 		// tmp = ft_substr(line, g_i - i, i); // free(tmp);
// 		ft_lstadd_back(&cmd->cmds, ft_lstnew(tmp));
// 	}
// 	printf("tmp else = %s\n",tmp);
// 	free(tmp);
// 	return (0);
// }

int		check_between_quotes(int i, char *line, char type)
{
	int		check;

	check = 0;
	while (line[i])
	{
		if (line[i] == type)
		{
			check++;
			break;
		}
		i++;
	}
	if (check == 0)
		return (1);
	return (0);
}

int		value_doll_length(char *line, int i)
{
	int		j;

	j = 0;
	while (line[i] && !end_doll(line[i]))
	{
		i++;
		j++;
	}
	return (j);
}

char	*value_doll(char *line, int i)
{
	char	*a_doll;
	int		j;
	
	j = value_doll_length(line, i);
	a_doll = ft_substr(line, i, j);
	return (a_doll);
}

int		quotes_length(char **env, int i, char *line, char type)
{
	int		l;

	l = 0;
	while (line[i] != ' ' && line[i] != '\0' && line[i] != type)
	{
		if (line[i] == '$' && type == '\"')
		{
			i++;
			l += get_env_length(env, line, i);
			ft_putstr_fd("in q doll l = ",1);
			ft_putendl_fd(ft_itoa(l),1);
			i += value_doll_length(line, i);
		}
		if (line[i] != '\0')
		{
			if (line[i] != type)
				l++;
			i++;
		}
	}
	ft_putstr_fd("in quotes l = ", 1);
	ft_putendl_fd(ft_itoa(l), 1);
	ft_putendl_fd(ft_itoa(g_i), 1);
	// printf("quotes = %d",l);
	return (l);
}

int		handle_quotes(char **env, t_cmd *cmd, char type, char *line)
{
	char	*tmp;
	int		i;
	char	*ret_q;
	int		j;
	char	*value_env;
	
	g_i++;
	i = 0;
	if (check_between_quotes(g_i, line, type))
		return (1);
	ret_q = malloc((quotes_length(env, g_i, line, type) + 1)  * sizeof(char));
	while (line[i] != ' ' && line[i] != '\0')
	{
		j = 0;
		if (line[i] == '$' && (type == '\"' && line[i - 1] != '\\'))//check $
		{
			g_i++;
			i++;
			tmp = value_doll(line, g_i);
			value_env = get_env_var(env, tmp);
			g_i += ft_strlen(tmp);
			printf("line = %c\n", line[g_i - 1]);
			while (value_env[j])
				ret_q[i++] = value_env[j++];
			if (ft_strcmp(tmp, "") == 0)
				ret_q[i++] = '$';
			free(value_env);
			free(tmp);
		}
		if (line[i] != type  && line[i] != '$')
			ret_q[i++] = line[g_i++];
		else if (line[i] != '\0')
		{
			g_i++;
			i++;
		}
		printf("%d\n", i);
	}
	ret_q[i] = '\0';
	if (ft_strcmp(ret_q, "") == 0 && line[g_i - 1] == '$')
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ft_strdup("$")));
	else
		ft_lstadd_back(&cmd->cmds, ft_lstnew(ret_q));
	// free(ret_q);
	return (0);
}