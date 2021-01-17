/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:12:26 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/17 18:38:43 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*ft_read_line()
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

void	signal_handler(int signal)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	if (signal == SIGINT)
	{
		g_cwd = get_current_working_directory();
		ft_putstr_fd("\n\e[1;92m-> \e[1;96mminishell \e[1;94m( \e[1;93m", 1);
		ft_putstr_fd(g_cwd, 1);
		ft_putstr_fd("\e[1;94m )", 1);
		ft_putstr_fd("\e[1;91m /# \e[0m", 1);
	}
}

int     main()
{
	extern char **environ;
	char	*line;
	t_cmd	cmd;
	
	signal(SIGINT, signal_handler);
	// signal(SIGQUIT, signal_handler);
	while (1)
	{
		g_cwd = get_current_working_directory();
		ft_putstr_fd("\e[1;92m-> \e[1;96mminishell \e[1;94m( \e[1;93m", 1);
		ft_putstr_fd(g_cwd, 1);
		ft_putstr_fd("\e[1;94m )", 1);
		ft_putstr_fd("\e[1;91m /# \e[0m", 1);
		line = ft_read_line();
		// if (!feof(stdin))
		// {
		// 	ft_putendl_fd("exit", 1);
		// 	exit(0);
		// }
		if (ft_strcmp(line, "") != 0)
		{
			// Parsing
			
			// Executing
			cmd.cmds = ft_lstnew("./test.sh");
			ft_lstadd_back(&cmd.cmds, ft_lstnew("executing"));
			// ft_lstadd_back(&cmd.cmds, ft_lstnew("hello"));

			check_command(&cmd, environ);
		}
		free(g_cwd);
	}
    return (0);
}