PROG	= minishell

SRCS 	= minishell.c \
		minishell_utils.c \
		builtin.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

LIBS = libft/libft.a
OBJS 	= ${SRCS:.c=.o} ${SRCS_LIBFT:.c=.o}
PROG_B = minishell_bonus

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g3

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: 		${PROG}

${PROG}:	${OBJS}
					@make -C libft/
					@cc ${OBJS} ${LIBS} -o ${PROG} -lreadline
					@echo "\nMinishell compiled!\n"

clean:

					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@rm -f $(NAME)
					@rm -f ${PROG} ${PROG_B}
					@echo "\nDelete ALL!\n"

re:			fclean all

re_bonus:	fclean bonus

.PHONY: all clean fclean re bonus

