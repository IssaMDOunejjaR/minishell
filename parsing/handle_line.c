/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:19:57 by ychennaf          #+#    #+#             */
/*   Updated: 2021/03/12 11:45:51 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	fill_tab2_2(char *line, char ***tab2)
{
	if (line[g_i] == '<')
	{
		g_i++;
		*tab2 = tab_join(*tab2, "<");
	}
	else if (line[g_i] == '>')
	{
		g_i++;
		if (line[g_i] == '>')
		{
			g_i++;
			*tab2 = tab_join(*tab2, ">>");
		}
		else
			*tab2 = tab_join(*tab2, ">");
	}
	else if (line[g_i] && (line[g_i] != ' ' && line[g_i] != '\t'))
		*tab2 = tab_join_f(*tab2, fill_tab(line));
	else
		g_i++;
}

char			**tab_join_f(char **tab, char *line)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(sizeof(char*) * (table_len_2d(tab) + 2));
	i = 0;
	while (tab[i] != NULL)
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(line);
	new_tab[++i] = NULL;
	free_table(tab);
	free(line);
	return (new_tab);
}

char			**fill_tab2(char *line)
{
	char	**tab2;

	tab2 = malloc(sizeof(char*) * 1);
	tab2[0] = NULL;
	while (line[g_i])
	{
		if (line[g_i] == ' ' || line[g_i] == '\t')
			g_i = skip_spaces(line, g_i);
		else if (line[g_i] == '|')
		{
			g_i++;
			tab2 = tab_join(tab2, "|");
		}
		else if (line[g_i] == ';')
		{
			g_i++;
			tab2 = tab_join(tab2, ";");
		}
		else
			fill_tab2_2(line, &tab2);
	}
	return (tab2);
}

char			*fill_tab(char *line)
{
	char	type;
	int		i;

	i = g_i;
	while (line[g_i] && (line[g_i] != ' ' && line[g_i] != '\t')
			&& line[g_i] != '|' && line[g_i] != ';'
			&& line[g_i] != '<' && line[g_i] != '>')
	{
		if (line[g_i] == '"' || line[g_i] == '\'')
		{
			type = line[g_i++];
			while (line[g_i] != type)
			{
				g_i++;
				if (line[g_i] == type && line[g_i - 1] == '\\' && type == '"')
					g_i++;
			}
			g_i++;
		}
		else
			g_i++;
	}
	return (ft_substr(line, i, g_i - i));
}
