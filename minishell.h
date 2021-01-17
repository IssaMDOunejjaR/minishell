/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:42:06 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/17 17:12:57 by iounejja         ###   ########.fr       */
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
	t_list	*files;
	t_type	type;
}				t_cmd;

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

#endif