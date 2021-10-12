# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/09 14:57:18 by iounejja          #+#    #+#              #
#    Updated: 2021/03/12 14:44:13 by ychennaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = minishell
SRCS = utils/ft_strcmp.c \
		utils/lst_file_new.c \
		utils/lst_file_add_back.c \
		utils/table_utils.c \
		parsing/parse.c \
		parsing/get_env.c \
		parsing/handle_quotes.c \
		parsing/check_line.c \
		parsing/handle_line.c \
		parsing/handle_cmd.c \
		parsing/handle_cmd2.c \
		parsing/fill_line.c \
		parsing/fill_line2.c \
		parsing/fill_line3.c \
		executing/check_commands.c \
		executing/command_utils.c \
		executing/check_and_execute.c \
		executing/files_handling.c \
		executing/env_var_utils.c \
		executing/execute_commands.c \
		executing/cd_utils.c \
		executing/more_utils.c \
		executing/built-in/pwd.c \
		executing/built-in/cd.c \
		executing/built-in/env.c \
		executing/built-in/export.c \
		executing/built-in/exit.c \
		executing/built-in/echo.c \
		executing/built-in/unset.c \
		main.c

OBJS = $(SRCS:.c=.o)

HEADERS = -I utils/libft -I .

all : $(NAME)

$(NAME): $(OBJS) | libft
	$(CC) $(FLAGS) $(HEADERS) $(OBJS) utils/libft/libft.a -o $(NAME)

clean:
	cd utils/libft && $(MAKE) clean
	rm -rf $(OBJS)

fclean: clean
	cd utils/libft && $(MAKE) fclean
	rm -f $(NAME)

libft:
	@cd utils/libft && $(MAKE)

re: fclean all

%.o : %.c minishell.h utils/libft/libft.h
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

