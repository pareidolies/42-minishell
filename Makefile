SRCS			=	parser/main_parser.c \
					parser/tokens_handler.c \
					parser/tokenization.c \
					parser/expander.c \
					parser/trim_tokens.c \
					parser/parser.c \
					exec/testmain.c \
					exec/exec_utils.c

BONUS			= 

SRCS_DIR		= srcs/

BONUS_DIR		= srcs_bonus/

SRCS_PATH	 	= $(SRCS:%=$(SRCS_DIR)%)

SRCS_B_PATH 	= $(BONUS:%=$(BONUS_DIR)%)

OBJS		 	= $(SRCS_PATH:%.c=%.o)

OBJS_BONUS		= $(SRCS_B_PATH:%.c=%.o)

NAME		 	= minishell

NAME_BONUS		= minishell

PATH_LIBFT		= -C libft --no-print-directory

LIBRARY			= ./libft/libft.a

INCS			= includes

RM		 		= rm -f

CC				= cc -Wall -Wextra -Werror 

all:			${NAME}

$(NAME):		${OBJS}
			$(MAKE) $(PATH_LIBFT)
			$(CC) -I $(INCS) $(SRCS_PATH) $(LIBRARY) -o $(NAME) -lreadline

clean:
			${RM} ${OBJS} ${OBJS_BONUS}
			$(MAKE) clean $(PATH_LIBFT)

fclean:			clean
			${RM} ${NAME} ${NAME_BONUS}
			$(MAKE) fclean $(PATH_LIBFT)

re:			fclean ${NAME}

bonus:			${OBJS_BONUS}
			$(MAKE) $(PATH_LIBFT)
			$(CC) -I $(INCS) $(SRCS_B_PATH) $(LIBRARY) -o $(NAME_BONUS)

.PHONY:			all clean fclean re bonus
