/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:42:06 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/11 18:05:07 by ychennaf         ###   ########.fr       */
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
char	*g_old_pwd;
int		g_i;
int		g_t;
char	*g_latest_cmd;

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
	struct s_file *next;
}				t_file;

typedef struct	s_cmd
{
	t_list	*cmds;
	t_file	*files;
	t_type	type;
}				t_cmd;
// Parsing
t_file  *lst_file_new(char *file, t_type type);
void    lst_file_add_back(t_file **alst, t_file *new);
int		get_command(char *line, char **env, t_cmd *cmd, char **tab2);
char	*get_env(char **env, char *line);
int		get_simple_s(char *line, t_cmd *cmd, char **env);
int		ft_strcmp(char *s1, char *s2);
int		handle_quotes(char **env, t_cmd *cmd, char type, char *line);
int		get_env_length(char **env, char *line, int i);
int		end_doll(char c);
int		check_between_quotes(int i, char *line, char type);
int		quotes_length(char **env, int i, char *line, char type);
int		value_doll_length(char *line, int i);
char	*value_doll(char *line, int i);
void	add_lsdoll(char **env, char *line, t_cmd *cmd);
void	init_cmd(t_cmd *cmd);
int		simple_length(char **env, int i, char *line);
void    free_commands(t_cmd *cmd);
int		check_line(char *line);
int		is_charm(char c);
int		check_pipe(char *line , int i);
int		check_app(char *line, int i);
int		check_semi(char *line, int i);
int		skip_spaces(char *line, int i);
char	**fill_tab2(char *line);
char	*fill_tab(char *line);
int		check_end_cmd(t_cmd *cmd, char **tab, char **env);
int		size_q(char *line, char **env, int *i, char type);
int		size_line(char *line, char **env);
void	handle_cmd(char *line, char **env, t_cmd *cmd);
char	*handle_file(char *line, char **env);
char	*fill_q(char *line, char **env, int *i, char type);
char	*fill_d(char *line, char **env, int *i);
int		check_backslash(char c);

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