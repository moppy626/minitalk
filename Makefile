# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:09:57 by mmachida          #+#    #+#              #
#    Updated: 2025/06/08 12:24:11 by mmachida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror
NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus
SRC_CLIENT = client.c data_tools.c telecom_tools.c
SRC_SERVER = server.c data_tools.c telecom_tools.c
SRC_CLIENT_BONUS = client_bonus.c data_tools.c telecom_tools.c
SRC_SERVER_BONUS = server_bonus.c data_tools.c telecom_tools.c
SRC_LIBFT = libft/libft.a
SRC_PRINTF = ft_printf.c printf_funcs.c str_funcs.c
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

OBJS_CLIENT = $(SRC_PRINTF:.c=.o) $(SRC_CLIENT:.c=.o) $(SRC_LIBFT)
OBJS_SERVER = $(SRC_PRINTF:.c=.o) $(SRC_SERVER:.c=.o) $(SRC_LIBFT)
OBJS_CLIENT_BONUS = $(SRC_PRINTF:.c=.o) $(SRC_CLIENT_BONUS:.c=.o) $(SRC_LIBFT)
OBJS_SERVER_BONUS = $(SRC_PRINTF:.c=.o) $(SRC_SERVER_BONUS:.c=.o) $(SRC_LIBFT)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):$(OBJS_CLIENT)
	@$(CC) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVER):$(OBJS_SERVER)
	@$(CC) $(OBJS_SERVER) -o $(NAME_SERVER)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS):$(OBJS_CLIENT_BONUS)
	@$(CC) $(OBJS_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS):$(OBJS_SERVER_BONUS)
	@$(CC) $(OBJS_SERVER_BONUS) -o $(NAME_SERVER_BONUS)

$(SRC_LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)

fclean:
	make -C libft fclean
	rm -f $(NAME_CLIENT) $(OBJS_CLIENT) $(NAME_SERVER) $(OBJS_SERVER) $(NAME_CLIENT_BONUS) $(OBJS_CLIENT_BONUS) $(NAME_SERVER_BONUS) $(OBJS_SERVER_BONUS)

re: fclean all

.PHONEY: bonus all clean fclean re
