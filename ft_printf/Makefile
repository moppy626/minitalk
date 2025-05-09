# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 10:22:43 by mmachida          #+#    #+#              #
#    Updated: 2024/08/14 16:56:25 by mmachida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a
CC	=	cc -Wall -Wextra -Werror
SRCS =	str_funcs.c ft_memcpy.c ft_strlen.c\
		printf_funcs.c ft_printf.c
all:	arall #cleanz
arall:	$(SRCS:.c=.o) 
		ar rc $(NAME) $(SRCS:.c=.o)
%.o:%.c 
		$(CC) -c $<
clean:
		rm -f $(SRCS:.c=.o)
fclean: clean
		rm -f $(NAME)
re:		fclean all
