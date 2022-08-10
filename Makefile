SRCS			=	lexer/parse_input.c \
					lexer/tokens_handler.c \
					parser/trimmer.c \
					parser/convert_tokens_to_commands.c \
					parser/commands_handler.c \
					lexer/check_tokens.c \
					parser/free_parser.c \
					parser/splitter.c \
					lexer/check_quotes.c \
					parser/redirections_handler.c \
					lexer/analyze_tokens.c \
					lexer/tokens_utils.c \
					parser/quotes_utils.c \
					expander/expander.c \
					expander/expander_utils.c \
					lexer/convert_input_to_tokens.c \
					exec/env_utils.c \
					exec/testmain.c \
					exec/ft_exec.c \
					exec/ft_heredoc.c \
					exec/gnl.c \
					exec/ft_fork.c \
					exec/redir.c \
					exec/pipes.c \
					exec/handle_fd.c \
					exec/exec_utils.c \
					exec/get_path.c \
					exec/child.c \
					exec/signals.c \
					utils/say_hello.c \
					builtin/builtin_utils.c \
					builtin/ft_cd.c \
					builtin/ft_echo.c \
					builtin/ft_env.c \
					builtin/ft_export.c \
					builtin/ft_pwd.c \
					builtin/ft_unset.c \
					builtin/ft_exit.c \
					utils/print_messages.c \
					utils/magic_malloc.c \

SRCDIR = srcs

OBJDIR = objs

SOURCES := ${addprefix ${SRCDIR}/, ${SRCS}}

OBJS	:= ${SOURCES:${SRCDIR}/%.c=${OBJDIR}/%.o}


NAME	= minishell

LFT		= libft/libft.a

INC		= -I ./includes -I ./libft

CC		= cc
RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror -g

LIBFLAGS	= -L./libft -lft -lreadline

${NAME}:	${LFT} ${OBJS}
			@echo "Created object files."
			@${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFLAGS}
			@echo "Minishell is ready!"
		
${OBJDIR}/%.o : ${SRCDIR}/%.c
		@[ ! -d ${OBJDIR} ] && mkdir -p  ${OBJDIR} || true
		@[ ! -d ${OBJDIR}/exec/ ] && mkdir -p  ${OBJDIR}/exec/ || true
		@[ ! -d ${OBJDIR}/parser/ ] && mkdir -p  ${OBJDIR}/parser/ || true
		@[ ! -d ${OBJDIR}/builtin/ ] && mkdir -p  ${OBJDIR}/builtin/ || true
		@[ ! -d ${OBJDIR}/utils/ ] && mkdir -p  ${OBJDIR}/utils/ || true
		@[ ! -d ${OBJDIR}/lexer/ ] && mkdir -p  ${OBJDIR}/lexer/ || true
		@[ ! -d ${OBJDIR}/expander/ ] && mkdir -p  ${OBJDIR}/expander/ || true
		@$(CC) $(CFLAGS) -c ${INC} $< -o $@

${LFT}:
		@echo " [..] | Compiling libft..."
		@make -s -C libft
		@echo " [OK] | Done."

all:		${NAME}

bonus:		${NAMEB}

sanitize:	${LFT}
		@${CC} ${CFLAGS} -fsanitize=address -g3 ${INC} ${SOURCES} -o ${NAME} ${LIBFLAGS}
		@${CC} ${CFLAGS} -fsanitize=address -g3 ${INC} ${SOURCESB} -o ${NAMEB} ${LIBFLAGS}
		@echo " Compiled with address sanitizer."


clean:		
		@${RM} ${OBJS}
		@${RM} ${OBJSB}
		@${RM} ${OBJDIR}
		@${RM} ${OBJBDIR}
		@echo "Object files removed."

fclean:		clean
		@${RM} ${NAME}
		@${RM} ${NAMEB}
		@make -s -C libft fclean
		@echo "Binary files removed."

re:		fclean all

.PHONY: all clean sanitize fclean re bonus

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

# BONUS			= 

# SRCS_DIR		= srcs/

# BONUS_DIR		= srcs_bonus/

# SRCS_PATH	 	= $(SRCS:%=$(SRCS_DIR)%)

# SRCS_B_PATH 	= $(BONUS:%=$(BONUS_DIR)%)

# OBJS		 	= $(SRCS_PATH:%.c=%.o)

# OBJS_BONUS		= $(SRCS_B_PATH:%.c=%.o)

# NAME		 	= minishell

# NAME_BONUS		= minishell

# PATH_LIBFT		= -C libft --no-print-directory

# LIBRARY			= ./libft/libft.a

# INCS			= includes

# RM		 		= rm -f

# CC				= cc -Wall -Wextra -Werror -fsanitize=address

# all:			${NAME}

# $(NAME):		${OBJS}
# 			$(MAKE) $(PATH_LIBFT)
# 			$(CC) -I $(INCS) $(SRCS_PATH) $(LIBRARY) -o $(NAME) -lreadline

# clean:
# 			${RM} ${OBJS} ${OBJS_BONUS}
# 			$(MAKE) clean $(PATH_LIBFT)

# fclean:			clean
# 			${RM} ${NAME} ${NAME_BONUS}
# 			$(MAKE) fclean $(PATH_LIBFT)

# re:			fclean ${NAME}

# bonus:			${OBJS_BONUS}
# 			$(MAKE) $(PATH_LIBFT)
# 			$(CC) -I $(INCS) $(SRCS_B_PATH) $(LIBRARY) -o $(NAME_BONUS)

# .PHONY:			all clean fclean re bonus
