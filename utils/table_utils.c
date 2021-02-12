/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:07:04 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 11:17:09 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		check_equal(char **tab, int i)
{
	int j;

	j = 0;
	while (tab[i][j] != '\0' && tab[i + 1] != NULL &&
	tab[i][j] == tab[i + 1][j])
		j++;
	return (j);
}

char			**sort_table_2d(char **tab)
{
	int		i;
	int		j;
	int		is_sorted;
	char	*tmp;

	is_sorted = 0;
	while (is_sorted == 0)
	{
		is_sorted = 1;
		i = 0;
		while (tab[i] != NULL)
		{
			j = check_equal(tab, i);
			if (tab[i + 1] != NULL && tab[i][j] > tab[i + 1][j])
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				is_sorted = 0;
			}
			i++;
		}
	}
	return (tab);
}

char			**copy_table_2d(char **tab)
{
	int		i;
	char	**new_tab;

	new_tab = malloc(sizeof(char*) * (table_len_2d(tab) + 1));
	i = 0;
	while (tab[i] != NULL)
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

char			**tab_join(char **tab, char *line)
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
	return (new_tab);
}

int				table_len_2d(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}
