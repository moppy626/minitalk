# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:09:57 by mmachida          #+#    #+#              #
#    Updated: 2025/06/08 17:57:34 by mmachida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror
NAME_CLIENT = client
NAME_SERVER = server
SRC_CLIENT = client.c data_tools.c telecom_tools.c
SRC_SERVER = server.c data_tools.c telecom_tools.c
SRC_LIBFT = libft/libft.a
SRC_PRINTF = ft_printf.c printf_funcs.c str_funcs.c
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

OBJS_CLIENT = $(SRC_PRINTF:.c=.o) $(SRC_CLIENT:.c=.o) $(SRC_LIBFT)
OBJS_SERVER = $(SRC_PRINTF:.c=.o) $(SRC_SERVER:.c=.o) $(SRC_LIBFT)

all: $(NAME_CLIENT) $(NAME_SERVER)

bonus: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):$(OBJS_CLIENT)
	@$(CC) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVER):$(OBJS_SERVER)
	@$(CC) $(OBJS_SERVER) -o $(NAME_SERVER)

$(SRC_LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean:
	make -C libft fclean
	rm -f $(NAME_CLIENT) $(OBJS_CLIENT) $(NAME_SERVER) $(OBJS_SERVER)

re: fclean all

.PHONEY: bonus all clean fclean re
