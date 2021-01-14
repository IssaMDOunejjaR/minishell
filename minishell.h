/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:42:06 by iounejja          #+#    #+#             */
/*   Updated: 2021/01/14 18:59:48 by iounejja         ###   ########.fr       */
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
void	command_is_valid(t_cmd *cmd, char **env);
void	check_command(t_cmd *cmd, char **env);

#endif