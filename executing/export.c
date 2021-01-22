/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issamdounejjar <issamdounejjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 19:46:37 by issamdounej       #+#    #+#             */
/*   Updated: 2021/01/19 20:00:35 by issamdounej      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **convert_env(char **env)
{
    int     i;
    char    **tmp;
    char    *value;
    char    **new;

    i = 0;
    new = malloc(sizeof(char*) * (table_len_2d(env) + 1));
    while (env[i] != NULL)
    {
        tmp = ft_split(env[i], '=');
        value = ft_strjoin("\"", tmp[1]);
        value = ft_strjoin(value, "\"");
        value = ft_strjoin("=", value);
        value = ft_strjoin(tmp[0], value);
        new[i] = ft_strjoin("declare -x ", value);
        i++;
    }
    new[i] = NULL;
    return (new);
}