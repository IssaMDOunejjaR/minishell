/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:12:26 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/27 16:24:57 by iounejja         ###   ########.fr       */
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

void	print_prompt()
{
	g_cwd = get_current_working_directory();
	if (g_error_value == 0)
		ft_putstr_fd("\e[1;92m-> ", 1);
	else
		ft_putstr_fd("\e[1;91m-> ", 1);
	ft_putstr_fd("\e[1;96mminishell \e[1;94m( \e[1;93m", 1);
	ft_putstr_fd(g_cwd, 1);
	ft_putstr_fd("\e[1;94m )", 1);
	ft_putstr_fd("\e[1;91m /# \e[0m", 1);
}

void	signal_handler(int signal)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		print_prompt();
	}
}

int     main()
{
	extern char	**environ;
	char		*line;
	t_cmd		cmd;
	
	signal(SIGINT, signal_handler);
	// signal(SIGQUIT, signal_handler);
	g_error_value = 0;
	while (1)
	{
		print_prompt();
		line = ft_read_line();
		// if (!feof(stdin))
		// {
		// 	ft_putendl_fd("exit", 1);
		// 	exit(0);
		// }
		if (ft_strcmp(line, "") != 0)
		{
			// Parsing
			// cmd = malloc(sizeof(t_cmd));
			// cmd->files = malloc(sizeof(t_file));
			get_command(line, environ, &cmd);
			// Executing
			cmd.cmds = ft_lstnew("cd");
			ft_lstadd_back(&cmd.cmds, ft_lstnew(".."));
			// ft_lstadd_back(&cmd.cmds, ft_lstnew("hello"));

			get_commands(&cmd, environ);
			// execute_command(&cmd);
			// char **test = convert_env(environ);
			// int i = 0;
			// while (test[i] != NULL)
			// {
			// 	ft_putendl_fd(test[i], 1);
			// 	i++;
			// }
		}
		free(g_cwd);
	}
    return (0);
}