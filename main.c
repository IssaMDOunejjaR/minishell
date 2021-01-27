/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:12:26 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/15 16:26:08 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

extern char	**environ;

char	*read_line()
{
	int		ret;
	char	buffer[BUFFER_SIZE];
	char	*line;
	char	*tmp;

	line = ft_strdup("");
	while ((ret = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
		if(ft_strchr(buffer, '\n'))
			break ;
	}
	line[ft_strlen(line) - 1] = '\0';
	return (line);
}

int     main()
{
	char	*line;
	t_cmd	cmd;

	while (1)
	{
		g_i = 0;
		write(1, "> ", 2);
		line = read_line();
		if (ft_strcmp(line, "") != 0)
		{
			// Parsing
			// cmd = malloc(sizeof(t_cmd));
			// cmd->files = malloc(sizeof(t_file));
			get_command(line, environ, &cmd);
			// Executing
			
			printf("~ %s\n", line);
		}
	}
    return (0);
}
