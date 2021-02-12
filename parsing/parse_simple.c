/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:45:06 by ychennaf          #+#    #+#             */
/*   Updated: 2021/02/12 17:18:31 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		simple_length(int i, char *line)
{
	int		l;
	char	type;

	l = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		if (line[i] == '$')
		{
			printf(">>> 1 %d <<<\n", i);
			i++;
			printf(">>> 2 %d <<<\n", i);
			l += get_env_length( line, i);
			printf(">>> 3 %d <<<\n", i);
			i += value_doll_length(line, i);
			printf(">>> 4 %d <<<\n", i);
		}
		if (line[i] == '\'' || line[i] == '\"')
		{
			// printf("ok %d\n", i);
			type = line[i]
;			i++;
			l += quotes_length( i, line, line[i - 1]) - 1;
			ft_putstr_fd("i = ",1);
			ft_putendl_fd(ft_itoa(i), 1);
			ft_putstr_fd("l = ",1);
			ft_putendl_fd(ft_itoa(l), 1);
			while(line[i] != '\'' && line[i] != '\"' && line[i] != '\0')
				i++;
			ft_putstr_fd("i = ",1);
			ft_putendl_fd(ft_itoa(i), 1);
		}
		if (line[i] != '\0' && line[i] != '$' && line[i] != ' ')
		{
			if (line[i] != type)
				l++;
			i++;
		}
	}
	ft_putstr_fd("l all = ",1);
	ft_putendl_fd(ft_itoa(l), 1);
	return (l);
}

char	*quotes_in_s(char type, char *line)
{
	char	*tmp;
	int		i;
	char	*ret_q;
	int		j;
	char	*value_env;
	
	// g_i++;
	i = 0;
	ret_q = ft_calloc((quotes_length( g_i, line, type) + 1), sizeof(char));
	// printf("ok\n");
	// printf("ret_q = |%zu|\n",ft_strlen(ret_q));
	ft_putstr_fd("ret_q = ", 1);
	ft_putendl_fd(ft_itoa((int)ft_strlen(ret_q)), 1);
	printf("im here 2 = %c\n", line[g_i]);
	while (line[g_i] && line[g_i] != type)
	{
		j = 0;
		if (line[g_i] == '$' && type == '\"')//check $
		{
			g_i++;
			printf("im here 3 = %c -- i = %d\n", line[g_i], g_i);
			tmp = value_doll(line, g_i);
			// printf("tmp = |%s|\n",tmp);
			value_env = get_env_var( tmp);
			// printf("value_env = |%s|\n",value_env);
			g_i += ft_strlen(tmp);
			// printf("tmp l = %zu\n", ft_strlen(tmp));
			while (value_env[j])
				ret_q[i++] = value_env[j++];
			printf("im ret_q = %s\n", ret_q);
			free(value_env);
			free(tmp);
			printf("im here 4 = |%c| -- i = %d\n", line[g_i], g_i);
		}
		if (line[g_i] != type && line[g_i] != '$')
			ret_q[i++] = line[g_i++];
		else if (type == '\'')
			ret_q[i++] = line[g_i++];
		else if (line[g_i + 1] == '\"')
			g_i += 2;
			
	}
	printf("im here 5 = |%c| -- i = %d\n", line[g_i], g_i);
	ft_putendl_fd("tebtob", 1);
	printf("q = |%zu|\n",ft_strlen(ret_q));
	if (ft_strcmp(ret_q, "") == 0 && line[g_i - 1] == '$')
	{
		free(ret_q);
		return(ft_strdup("$"));
	}
	return (ret_q);
	// free(ret_q);
	// return (0);
}

int	get_simple_s(char *line, t_cmd *cmd, char **env)
{
	char	*tmp;
	int		i;
	char	*ret_q;
	int		j;
	char	*value_env;
	
	// g_i++;
	i = 0;
	ret_q = malloc((simple_length( g_i, line) + 1) *  sizeof(char));
	// printf("ret_q strlen = %d\n",(simple_length( g_i, line)));
	while (line[g_i] != '\0' && line[g_i] != ' ')
	{
		j = 0;
		// ft_putendl_fd(ft_itoa(g_i), 1);
		if ((line[g_i] == '\'' || line[g_i] == '\"')) // && line[g_i - 1] != '\\' !!!!!!!!!!!
		{
			g_i++;
			printf("im here = %c\n", line[g_i]);
			if (check_between_quotes(g_i, line, line[g_i - 1]))
				return (1);
			tmp = quotes_in_s( line[g_i - 1], line);
			while (tmp[j])
				ret_q[i++] = tmp[j++];
			free(tmp);
			// printf("im here 2= %c\n", line[g_i]);
			ft_putstr_fd("bbbbb = ",1);
			ft_putendl_fd(ft_itoa(g_i), 1);
			g_i += quotes_length( g_i, line, line[g_i - 1]);
			ft_putstr_fd("bbbbb = ",1);
			ft_putendl_fd(ft_itoa(g_i), 1);
			ft_putendl_fd("teteteteetete", 1);
			//g_i += 6;
		}
		else if (line[g_i] == '$')//check $
		{
			j = 0;
			g_i++;
			tmp = value_doll(line, g_i);
			// printf("tmp = |%s|\n",tmp);
			value_env = get_env_var( tmp);
			// printf("value_env = |%s|\n",value_env);
			g_i += ft_strlen(tmp);
			// printf("tmp l = %zu\n", ft_strlen(tmp));
			while (value_env[j])
				ret_q[i++] = value_env[j++];
			if (ft_strcmp(tmp, "") == 0)
				ret_q[i++] = '$';
			free(value_env);
			free(tmp);
		}
		else if (line[g_i] != '\0' && line[g_i] != ' ' && line[g_i] != '$')
			ret_q[i++] = line[g_i++];
		// printf("%c\n", line[g_i]);
		// if ((line[g_i] == '\'' || line[g_i] == '\"') && line[g_i - 1] != '\\')
		// 	g_i++;
	}
	
	ret_q[i] = '\0';
	// printf("simple = |%s|\n",ret_q);
	ft_putstr_fd("simple = ", 1);
	ft_putendl_fd(ret_q, 1);
	
	// free(ret_q);
	// cmd = NULL;
	ft_lstadd_back(&cmd->cmds, ft_lstnew(ret_q));
	// free(ret_q);
	return (0);
}