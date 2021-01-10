# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/09 14:57:18 by iounejja          #+#    #+#              #
#    Updated: 2021/01/10 15:02:34 by iounejja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = minishell
NAME = minishell.a
SRCS = ft_strcmp.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		cd utils/libft && make
		ar rcs $(NAME) $(OBJS) utils/libft/*.o

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf *.o
	cd utils/libft &&  make clean

fclean: clean
		rm -rf $(NAME)
		cd utils/libft && make fclean

re: fclean all