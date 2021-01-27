/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:42:06 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/27 16:00:19 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 100

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "utils/libft/libft.h"

char	*g_cwd;
int		g_error_value;

int		g_i;

typedef enum 	s_type
{
	WRITE,
	READ,
	APPEND,
	PIPE,
	END
}				t_type;

typedef struct	s_file
{
	char	*file;
	t_type	type;
}				t_file;

typedef struct	s_cmd
{
	t_list	*cmds;
	t_file	*files;
	t_type	type;
}				t_cmd;
// Parsing
int		get_command(char *line, char **env, t_cmd *cmd);
char	*get_env(char **env, char *line);
char	*get_simple_s(char *line);
int     ft_strcmp(char *s1, char *s2);

// Executing Section
void	check_command(t_cmd *cmd, char **env);
void	free_table(char **tab);
int		table_len_2d(char **tab);
char	**sort_table_2d(char **tab);
char	**copy_table_2d(char **tab);
char	**tab_join(char **tab, char *line);
char	*get_current_working_directory();
void	change_directory(t_cmd *cmd);
void	print_cwd();
void	print_env(char **env);
char	*get_env_var(char **env, char *name);
char    **convert_env(char **env);
void    execute_command(t_cmd *cmd);
void	get_commands(t_cmd *cmd, char **env);
void	exit_shell();

#endif