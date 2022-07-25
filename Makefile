SRCS			=	parser/main_parser.c \
					parser/tokens_handler.c \
					parser/tokenization.c \
					parser/expander.c \
					parser/trim_tokens.c \
					parser/parser.c \
					parser/commands_handler.c \
					parser/check_tokens.c \
					parser/redirections.c \
					exec/testmain.c \
					exec/exec_utils.c \

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

CC				= cc -Wall -Wextra -Werror -fsanitize=address

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

# SRCS			=	parser/main_parser.c \
# 					parser/tokens_handler.c \
# 					parser/tokenization.c \
# 					parser/expander.c \
# 					parser/trim_tokens.c \
# 					parser/parser.c \
# 					parser/commands_handler.c \
# 					parser/check_tokens.c \
# 					parser/redirections.c \
# 					exec/testmain.c \
# 					exec/exec_utils.c \
# 					builtin/cd.c \
# 					builtin/echo.c \
# 					builtin/env.c \
# 					builtin/export.c \
# 					builtin/pwd.c \
# 					builtin/unset.c \
# 					builtin/builtin_utils.c

# SRCDIR = srcs

# OBJDIR = objs

# SOURCES := ${addprefix ${SRCDIR}/, ${SRCS}}
# OBJS	:= ${SOURCES:${SRCDIR}/%.c=${OBJDIR}/%.o}


# NAME	= minishell

# LFT		= libft/libft.a

# INC		= -I ./includes -I ./libft

# CC		= cc
# RM		= rm -rf

# CFLAGS	= -Wall -Wextra -Werror

# LIBFLAGS	= -L./libft -lft -lreadline

# ${NAME}:	${LFT} ${OBJS}
# 			@echo "Created object files."
# 			@${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFLAGS}
# 			@echo "Minishell is ready!"
		
# ${OBJDIR}/%.o : ${SRCDIR}/%.c
# 		@[ ! -d ${OBJDIR} ] && mkdir -p  ${OBJDIR} || true
# 		@$(CC) $(CFLAGS) -c ${INC} $< -o $@

# ${LFT}:
# 		@echo " [..] | Compiling libft..."
# 		@make -s -C libft
# 		@echo " [OK] | Done."

# all:		${NAME}

# bonus:		${NAMEB}

# sanitize:	${LFT}
# 		@${CC} ${CFLAGS} -fsanitize=address -g3 ${INC} ${SOURCES} -o ${NAME} ${LIBFLAGS}
# 		@${CC} ${CFLAGS} -fsanitize=address -g3 ${INC} ${SOURCESB} -o ${NAMEB} ${LIBFLAGS}
# 		@echo " Compiled with address sanitizer."


# clean:		
# 		@${RM} ${OBJS}
# 		@${RM} ${OBJSB}
# 		@${RM} ${OBJDIR}
# 		@${RM} ${OBJBDIR}
# 		@echo "Object files removed."

# fclean:		clean
# 		@${RM} ${NAME}
# 		@${RM} ${NAMEB}
# 		@make -s -C libft fclean
# 		@echo "Binary files removed."

# re:		fclean all

# .PHONY: all clean sanitize fclean re bonus