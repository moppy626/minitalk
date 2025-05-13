#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf/ft_printf.h"
#include "libft/libft.h"

#include <stdio.h>

# define EOT		0x04
# define WAIT_TIME	10000

typedef struct s_data{
	int		p_id;
	int		ary[8];
	ssize_t idx;
	char	*str;
	ssize_t	len;
	struct s_data	*next;
} t_data;
