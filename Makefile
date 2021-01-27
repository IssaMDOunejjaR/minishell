# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/09 14:57:18 by iounejja          #+#    #+#              #
#    Updated: 2021/01/27 15:58:45 by ychennaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = minishell
NAME = minishell.a
SRCS = utils/ft_strcmp.c \
		parsing/parse.c \
		parsing/parse_simple.c \
		parsing/get_env.c \
		executing/check_commands.c \
		executing/table_utils.c \
		executing/pwd.c \
		executing/cd.c \
		executing/env.c \
		executing/export.c \
		executing/execute_command.c \
		executing/exit.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	gcc -Wall -Wextra -Werror main.c $(NAME) -o $(EXEC)

$(NAME): $(OBJS)
		cd utils/libft && make bonus
		ar rcs $(NAME) $(OBJS) utils/libft/*.o

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf *.o
	rm -rf utils/*.o
	rm -rf parsing/*.o
	rm -rf executing/*.o
	cd utils/libft &&  make clean

fclean: clean
		rm -rf $(NAME)
		cd utils/libft && make fclean

re: fclean all