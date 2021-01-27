/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:42:06 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/27 15:04:19 by ychennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 100

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "utils/libft/libft.h"
# include "executing/executing.h"

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

#endif

// 1 - content = echo -n test dsfh sghdh || next-> NULL ; file_content = txt || next-> NULL ; type = WRITE
// 2 - content = ls || next->NULL ; file = NULL ; type = 
// 1 - content = echo || next -> -n || next -> test || next -> dsfh || next -> sghdh || next -> NULL ;