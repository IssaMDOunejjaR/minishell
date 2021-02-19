# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:08:59 by iounejja          #+#    #+#              #
#    Updated: 2021/02/18 18:09:54 by iounejja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =	ft_memset.c \
	  	ft_bzero.c \
	  	ft_memcpy.c \
	  	ft_memccpy.c \
	  	ft_memmove.c \
	  	ft_memchr.c \
	  	ft_memcmp.c \
	  	ft_strlen.c \
	  	ft_isalpha.c \
	  	ft_isdigit.c \
	  	ft_isalnum.c \
	  	ft_isascii.c \
	  	ft_isprint.c \
	  	ft_toupper.c \
	  	ft_tolower.c \
	  	ft_strchr.c \
	  	ft_strrchr.c \
	  	ft_strncmp.c \
	  	ft_strlcpy.c \
	  	ft_strlcat.c \
	  	ft_strnstr.c \
	  	ft_atoi.c \
	  	ft_calloc.c \
	  	ft_strdup.c \
	  	ft_substr.c \
	  	ft_strjoin.c \
	  	ft_strtrim.c \
	  	ft_split.c \
	  	ft_itoa.c \
	  	ft_strmapi.c \
	  	ft_putchar_fd.c \
	  	ft_putstr_fd.c \
	  	ft_putendl_fd.c \
	  	ft_putnbr_fd.c \
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@ar rcs $(NAME) $(OBJ)

%.o : %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f *.o

fclean:	clean
		rm -f $(NAME)

re: fclean all
