/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:42:06 by iounejja          #+#    #+#             */
/*   Updated: 2021/02/13 17:15:27 by ychennaf         ###   ########.fr       */
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

char				*g_cwd;
char				*g_old_pwd;
char				*g_latest_cmd;
char				**g_env;
int					g_error_value;
int					g_t;
int					g_i;
int					g_prev_fd_read;
int					g_prev_type;
int					g_check;

typedef enum		e_type
{
	WRITE,
	READ,
	APPEND,
	PIPE,
	END
}					t_type;

typedef struct		s_file
{
	char			*file;
	t_type			type;
	struct s_file	*next;
}					t_file;

typedef struct		s_cmd
{
	t_list	*cmds;
	t_file	*files;
	t_type	type;
}					t_cmd;

t_file				*lst_file_new(char *file, t_type type);
void				lst_file_add_back(t_file **alst, t_file *new);
int					get_command(t_cmd *cmd, char **tab2);
char				*get_env(char *line);
int					get_simple_s(char *line, t_cmd *cmd, char **env);
int					ft_strcmp(char *s1, char *s2);
int					handle_quotes(t_cmd *cmd, char type, char *line);
int					get_env_length(char *line, int i);
int					end_doll(char c);
int					check_between_quotes(int i, char *line, char type);
int					quotes_length(int i, char *line, char type);
int					value_doll_length(char *line, int i);
char				*value_doll(char *line, int i);
void				add_lsdoll(char *line, t_cmd *cmd);
void				init_cmd(t_cmd *cmd);
int					simple_length(int i, char *line);
int					check_line(char *line);
int					is_charm(char c);
int					check_pipe(char *line, int i);
int					check_app(char *line, int i);
int					check_semi(char *line, int i);
int					skip_spaces(char *line, int i);
char				**fill_tab2(char *line);
char				*fill_tab(char *line);
int					check_end_cmd(t_cmd *cmd, char **tab);
int					size_q(char *line, int *i, char type);
int					size_line(char *line);
void				handle_cmd(char *line, t_cmd *cmd);
char				*handle_file(char *line);
char				*fill_q(char *line, int *i, char type);
char				*fill_d(char *line, int *i);
int					check_backslash(char c);
char				*fill_d2(char *tmp, int *i);
void				fill_ret(char *vl_env, char *ret, int *j);
void				free2(char *s1, char *s2);
void				fill_q2(char *line, int *i, int *k, char *ret);
int					size_q_b(char *line, int i, char type);
int					size_q_b2(char *line, int i, char type, int *l);
int					size_q2(char *line, int *i, char type);
int					check_end_cmd2(t_cmd *cmd, char **tab);
void				handle2(char *tmp, char *ret, int *j);
int					fill_qd(char **tmp, char *line, int i);
char				**tab_join_f(char **tab, char *line);
char				*alloc_q(int *k, int *i, char *ret, char *line);
int					check_backslash2(char *line, int *i, char type);
int					lenght_digit(int n);

void				get_commands(t_cmd *cmd, char *line);
void				execute_commands(t_cmd *cmd, char **tab);
void				check_command(t_cmd *cmd);
void				check_if_file_executable(t_cmd *cmd);
void				command_is_valid(t_cmd *cmd);
void				command_exe(t_cmd *cmd);
int					check_built_in(t_cmd *cmd);
void				exec_built_in(t_cmd *cmd);

void				free_table(char **tab);
int					table_len_2d(char **tab);
char				**sort_table_2d(char **tab);
char				**copy_table_2d(char **tab);
char				**tab_join(char **tab, char *line);
t_file				*lst_file_new(char *file, t_type type);
void				lst_file_add_back(t_file **alst, t_file *new);
void				free_commands(t_cmd *cmd);
int					is_all_num(char *str);
char				**get_args(t_cmd *cmd);

char				**init_global(void);
int					find_env_var(char *env_var);
char				*get_current_working_directory(void);
void				change_directory(t_cmd *cmd);
void				print_pwd(void);
char				*get_env_var(char *name);
void				exit_shell(t_cmd *cmd);
void				ft_echo(t_cmd *cmd);
void				ft_export(t_cmd *cmd);
int					check_files(t_cmd *cmd);
void				ft_unset(t_cmd *cmd);
void				print_export(void);
char				**delete_env_var(char *env_var);
char				**change_env_var(char *env_var);
int					export_check_special_carac(char *str);
int					unset_check_special_carac(char *str);
void				print_error(char *command, char *content, char *error);
void				print_env(void);
void				get_latest_cmd(t_cmd *cmd);
char				**split_export(char *str, char **tmp);
char				**convert_env(void);

#endif
