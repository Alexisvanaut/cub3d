NAME = libftprintf.a

CC = cc
FLAGS = -Wall -Wextra -Werror

SRC = 			ft_putchar.c	ft_printf.c		ft_putstr.c		ft_parsing.c	ft_print_hex.c \
				ft_putnbr.c


OBJ = $(SRC:.c=.o)

HEADER = ft_printf.h

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
