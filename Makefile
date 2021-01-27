# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychennaf <ychennaf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/09 14:57:18 by iounejja          #+#    #+#              #
#    Updated: 2021/01/27 15:37:59 by ychennaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = minishell
NAME = minishell.a
SRCS = utils/ft_strcmp.c \
		parsing/parse.c \
		parsing/parse_simple.c \
		parsing/get_env.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		cd utils/libft && make bonus
		ar rcs $(NAME) $(OBJS) utils/libft/*.o

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf *.o
	rm -rf utils/*.o
	rm -rf parsing/*.o
	cd utils/libft &&  make clean

fclean: clean
		rm -rf $(NAME)
		cd utils/libft && make fclean

re: fclean all