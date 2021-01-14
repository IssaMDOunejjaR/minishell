/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:12:26 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/14 19:08:23 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

extern char **environ;

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
	// char	*line;
	t_cmd	cmd;
	
	cmd.cmds = ft_lstnew("cat");
	ft_lstadd_back(&cmd.cmds, ft_lstnew("-n"));
	ft_lstadd_back(&cmd.cmds, ft_lstnew("hello"));

	check_command(&cmd, environ);
	// while (1)
	// {
	// 	write(1, "\e[1;92m-> \e[1;96mminishell\e[1;91m /# \e[0m", 41);
	// 	line = read_line();
	// 	if (ft_strcmp(line, "") != 0)
	// 	{
	// 		// Parsing
			
	// 		// Executing
			
	// 		printf("~ %s\n", line);
	// 	}
	// }
    return (0);
}