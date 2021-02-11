/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:42:06 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 11:22:59 by iounejja         ###   ########.fr       */
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
char	*g_old_pwd;
char	*g_latest_cmd;
int		g_error_value;
int		g_i;
int		g_prev_fd_read;
int		g_prev_type;

int		test;

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
	struct	s_file *next;
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
char	**get_commands(t_cmd *cmd, char **env);
char	**execute_commands(t_cmd *cmd, char **env);
char	**check_command(t_cmd *cmd, char **env);
void	check_if_file_executable(t_cmd *cmd, char **env);
void	command_is_valid(t_cmd *cmd, char **env);
void	command_exe(t_cmd *cmd, char **env);
int		check_built_in(t_cmd *cmd);
char	**exec_built_in(t_cmd *cmd, char **env);
char	**execute_commands(t_cmd *cmd, char **env);


void	free_table(char **tab);
int		table_len_2d(char **tab);
char	**sort_table_2d(char **tab);
char	**copy_table_2d(char **tab);
char	**tab_join(char **tab, char *line);
t_file	*lst_file_new(char *file, t_type type);
void	lst_file_add_back(t_file **alst, t_file *new);
void	free_commands(t_cmd *cmd);
t_list	*check_more_args(t_cmd *cmd);

char	**init_global(char **env);
char	*get_current_working_directory();
char	**change_directory(t_cmd *cmd, char **env);
void	print_pwd();
char	*get_env_var(char **env, char *name);
void	exit_shell(t_cmd *cmd, char **env);
void	ft_echo(t_cmd *cmd);
char    **ft_export(t_cmd *cmd, char **env);
int		check_files(t_cmd *cmd);
int		find_env_var(char **env, char *env_var);
char	**ft_unset(t_cmd *cmd, char **env);
void    print_export(char **env);
char	**delete_env_var(char **env, char *env_var);
char	**change_env_var(char *env_var, char **env);
int		check_special_carac(char *str);
int		is_all_num(char *str);
void	print_error(char *command, char *content, char *error);
void	print_env(char **env);

#endif