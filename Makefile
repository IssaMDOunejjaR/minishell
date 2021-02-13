# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/09 14:57:18 by iounejja          #+#    #+#              #
#    Updated: 2021/02/13 17:00:21 by iounejja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = minishell
NAME = minishell.a
SRCS = utils/ft_strcmp.c \
		utils/lst_file_new.c \
		utils/lst_file_add_back.c \
		utils/table_utils.c \
		parsing/parse.c \
		parsing/parse_simple.c \
		parsing/get_env.c \
		parsing/handle_quotes.c \
		parsing/free_cmd.c \
		parsing/check_line.c \
		parsing/handle_line.c \
		parsing/handle_cmd.c \
		parsing/handle_cmd2.c \
		parsing/fill_line.c \
		parsing/fill_line2.c \
		executing/check_commands.c \
		executing/command_utils.c \
		executing/check_and_execute.c \
		executing/files_handling.c \
		executing/env_var_utils.c \
		executing/execute_commands.c \
		executing/more_utils.c \
		executing/built-in/pwd.c \
		executing/built-in/cd.c \
		executing/built-in/env.c \
		executing/built-in/export.c \
		executing/built-in/exit.c \
		executing/built-in/echo.c \
		executing/built-in/unset.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	gcc -Wall -Wextra -Werror main.c $(NAME) -o $(EXEC)

$(NAME): $(OBJS)
		cd utils/libft && make bonus
		ar rcs $(NAME) $(OBJS) utils/libft/*.o

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@ -I .

clean:
	rm -rf *.o
	rm -rf utils/*.o
	rm -rf parsing/*.o
	rm -rf executing/*.o
	rm -rf executing/built-in/*.o
	cd utils/libft &&  make clean

fclean: clean
		rm -rf $(NAME)
		cd utils/libft && make fclean

re: fclean all