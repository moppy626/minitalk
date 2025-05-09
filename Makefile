# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:09:57 by mmachida          #+#    #+#              #
#    Updated: 2025/04/22 21:09:57 by mmachida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = sudo cc -Wall -Wextra -Werror
NAME_CLIENT = client
NAME_SERVER = server
SRC_CLIENT = client.c
SRC_SERVER = server.c
SRC_LIBFT = ft_atoi.c
SRC_PRINTF = ft_printf.c ft_memcpy.c ft_strlen.c printf_funcs.c str_funcs.c

SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

OBJS_CLIENT = $(SRC_PRINTF:.c=.o) $(SRC_LIBFT:.c=.o) $(SRC_CLIENT:.c=.o)
OBJS_SERVER = $(SRC_PRINTF:.c=.o) $(SRC_LIBFT:.c=.o) $(SRC_SERVER:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):$(OBJS_CLIENT)
	@$(CC) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVER):$(OBJS_SERVER)
	@$(CC) $(OBJS_SERVER) -o $(NAME_SERVER)

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean:
	rm -f $(NAME_CLIENT) $(OBJS_CLIENT) $(NAME_SERVER) $(OBJS_SERVER)

re: fclean all
