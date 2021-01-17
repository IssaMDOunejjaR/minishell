/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:07:04 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/16 16:50:13 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**sort_table_2d(char **tab)
{
	char	*tmp;
	int		i;
	int		is_sorted;
	
	is_sorted = 0;
	while (is_sorted == 0)
	{
		is_sorted = 1;
		i = 0;
		while (tab[i] != NULL)
		{
			if (tab[i + 1] != NULL && tab[i][0] > tab[i + 1][0])
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

char	**copy_table_2d(char **tab)
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

char	**tab_join(char **tab, char *line)
{
	char	**new_tab;
	int		i;
	
	new_tab = malloc(sizeof(char*) * (table_len_2d(tab) + 2));
	i = 0;
	while(tab[i] != NULL)
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(line);
	new_tab[++i] = NULL;
	free_table(tab);
	return (new_tab);
}

int		table_len_2d(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}