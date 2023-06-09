GCC     = gcc
CFLAGS  = -g -Wall -Wextra -Werror -fPIC -fPIE
FILES   = SRC/minishell.c SRC/cmdtrim.c SRC/expander.c SRC/cmdsubsplit.c SRC/signals.c \
		  SRC/fill_list.c SRC/executor.c SRC/builtin.c SRC/heredoc.c SRC/error.c SRC/unset_export.c \
		  SRC/subsplit_utils.c SRC/cmdtrim_utils.c SRC/exec_utils.c SRC/list_helper.c SRC/expander_helper.c \
		  SRC/utils.c
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