NAME = libftprintf.a

SRC = SRC/ft_printf.c SRC/ft_puthex.c SRC/ft_countdigits.c SRC/ft_p.c SRC/ft_putunsignednbr.c SRC/ft_print_cs.c SRC/ft_print_diu.c SRC/ft_print_x.c \
SRC/ft_printstate1.c SRC/ft_helphex.c SRC/ft_print_pcent.c SRC/ft_print_ptr.c SRC/ft_printstate0.c SRC/ft_print_hash.c SRC/ft_print_space.c \
SRC/ft_print_plus.c

SRC_OBJ = $(SRC:.c=.o)

MFLAGS = clean

HEAD = ft_printf.h

FLAGS = -Wall -Wextra -Werror -g

CC = gcc

all : $(NAME)

$(NAME): $(SRC_OBJ) $(HEAD)
	$(MAKE) -C Libft/
	$(MAKE) bonus -C Libft/
	$(MAKE) clean -C Libft/
	cp Libft/libft.a $(NAME)
	$(AR) -r $@ $?

.o: %.c
	$(CC) -c $(FLAGS) $@ $?

bonus: all
	
clean:
	rm -f $(SRC_OBJ)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C Libft/
re: fclean all
