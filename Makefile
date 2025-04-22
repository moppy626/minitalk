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

OBJS_CLIENT = $(SRC_CLIENT:.c=.o)
OBJS_SERVER = $(SRC_SERVER:.c=.o)

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
