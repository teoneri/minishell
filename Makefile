GCC     = gcc
CFLAGS  = -g -Wall -Wextra -Werror -fPIC -fPIE
FILES   = SRC/minishell.c SRC/pipesplit.c SRC/cmdtrim.c SRC/expander.c SRC/cmdsubsplit.c SRC/signals.c \
		  SRC/fill_list.c SRC/executor.c
NAME    = minishell
BONUS_NAME = checker
PRINTF  = ft_printf
LIBFT = libft
LIBRARY = ft_printf/libftprintf.a
RM  = rm -f
OBJECTS=$(FILES:.c=.o)
BONUS_OBJ = $(SRC_BONUS:.c=.o)

all:    $(NAME)
$(NAME):    $(OBJECTS)
						@make -C $(PRINTF)
						$(GCC) $(CFLAGS) $(OBJECTS) $(LIBRARY) -lreadline -o $(NAME)
clean:
						@$(RM) $(OBJECTS)
						@$(RM) $(BONUS_OBJ)
						@make clean -C $(PRINTF)

fclean: clean
						@$(RM) $(NAME)
						@$(RM) $(BONUS_NAME)
						@$(RM) $(LIBRARY)

re:     fclean all
bonus:          all $(BONUS_OBJ)
						
.PHONY:     all clean fclean re