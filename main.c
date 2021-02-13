/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:12:26 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 16:55:25 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_line(void)
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
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (!ret)
	{
		free(line);
		return (NULL);
	}
	line[ft_strlen(line) - 1] = '\0';
	return (line);
}

void	print_prompt(void)
{
	g_cwd = get_current_working_directory();
	if (g_error_value == 0)
		ft_putstr_fd("\e[1;92m~> ", 1);
	else
		ft_putstr_fd("\e[1;91m~> ", 1);
	ft_putstr_fd("\e[1;96mminishell \e[1;94m(\e[1;93m", 1);
	ft_putstr_fd(g_cwd, 1);
	ft_putstr_fd("\e[1;94m)", 1);
	ft_putstr_fd("\e[1;91m /# \e[0m", 1);
}

void	signal_handler(int signal)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	if (signal == SIGINT && g_check == 0)
	{
		ft_putchar_fd('\n', 1);
		free(g_cwd);
		print_prompt();
	}
}

void	handle_ctrl_d(char *line)
{
	ft_putendl_fd("exit", 1);
	free(line);
	free(g_cwd);
	free_table(g_env);
	free(g_latest_cmd);
	exit(g_error_value);
}

int		main(void)
{
	extern char	**environ;
	char		*line;
	t_cmd		cmd;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_env = copy_table_2d(environ);
	g_env = init_global();
	while (1)
	{
		print_prompt();
		line = ft_read_line();
		if (!line)
			handle_ctrl_d(line);
		if (ft_strcmp(line, "") != 0)
			get_commands(&cmd, line);
		free(g_cwd);
		free(line);
	}
	return (0);
}
