/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:12:26 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 18:05:28 by ychennaf         ###   ########.fr       */
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
	char		**tab2;
	char		*line;
	t_cmd		cmd;
	char		**env;
	g_old_pwd = "test";
	g_latest_cmd = "latest_cmd";
	int	x;
	int		check;
	
	// signal(SIGINT, signal_handler);
	// signal(SIGQUIT, signal_handler);
	g_error_value = 0;
	env = copy_table_2d(environ);
	// line = ft_strdup("echo \"fekfheo\'$USER\"");
	// printf("line = |%s|\n",line);
	// g_i = 0;
	// if (get_command(line, env, &cmd) == 0)
	// 	printf("ERROR\n");
	// free(line);
	while (1)
    {
		check = 0;
		// ft_putstr_fd("> ", 1);
		g_i = 0;
		g_t = 0;
        print_prompt();
        line = ft_read_line();
        // if (!feof(stdin))
        // {
        //  ft_putendl_fd("exit", 1);
        //  exit(0);
        // }
        if (ft_strcmp(line, "") != 0)
        {
			t_list *tmp;
			t_file *tmp2;
            // Parsing
            // cmd = malloc(sizeof(t_cmd));
            // cmd->files = malloc(sizeof(t_file));
			// if (check_line(line) == 1)
			// 	printf("ERROR\n");
			if (check_line(line) == 1)
			{
				check++;
				printf("ERROR\n");
			}
			else
			{
					tab2 = fill_tab2(line);
				int i = 1;
					while ((x = get_command(line, env, &cmd, tab2)))
					{
						printf("command  -- %d --\n", i++);
						tmp = cmd.cmds;
						tmp2 = cmd.files;
						while (cmd.cmds != NULL)
						{
							printf("|%s|\n", cmd.cmds->content);
							cmd.cmds = cmd.cmds->next;
						}
						printf("cmd_type => %d\n", cmd.type);
						while (cmd.files != NULL)
						{
							printf("file = %s || type = %d\n", cmd.files->file, cmd.files->type);
							cmd.files= cmd.files->next;
						}
						cmd.cmds = tmp;
						cmd.files = tmp2;
						free_commands(&cmd);
						if (x == 2)
							break;	
					}
				free_commands(&cmd);
			}
			// if (x == 0)
			// 	printf("ERROR\n");
            // if (get_command(line, env, &cmd) == 0)
            // Executing
            // cmd.cmds = ft_lstnew("/bin/ls");
            // ft_lstadd_back(&cmd.cmds, ft_lstnew("-la"));
            // ft_lstadd_back(&cmd.cmds, ft_lstnew("hello"));
            // get_commands(&cmd, env);
			// printf("moi sortir\n");
			// free_commands(&cmd);
			if (check == 0)
				free_table(tab2);
        }
		free(line);
        free(g_cwd);
    }
	free_table(env);
    return (0);
}
//echo test$USER "$PATH"