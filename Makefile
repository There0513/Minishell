# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: threiss <threiss@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 14:30:28 by threiss           #+#    #+#              #
#    Updated: 2022/02/16 22:38:35 by threiss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PATH	=	./srcs/

SRCS_NAMES	=	main_tools.c main.c main_tools_two.c \
			
SRCS_SIGNAL	=	signal/main.c

SRCS_ENV	=	environment/tools.c environment/main_tools.c \
				environment/main.c environment/dollar_tools.c \
				environment/dollar_tools_two.c environment/dollar_tools_three.c \
				environment/dollar_tools_four.c

SRCS_BUILT	=	builtin/search_builtin.c builtin/pwd.c builtin/unset.c \
				builtin/echo.c builtin/env.c builtin/cd_three.c \
				builtin/cd_two.c builtin/cd.c builtin/ft_export_three.c \
				builtin/ft_export_two.c builtin/ft_export.c builtin/exit.c \
				builtin/unset_two.c builtin/ft_export_four.c

SRCS_EXEC	=	executable/execution_tools.c \
				executable/execution.c executable/exec_prep.c \
				executable/exec_tools.c executable/no_pipe.c \
				executable/handle_fds.c executable/here_doc_exec_prep.c \
				executable/no_pipe_tools.c

SRCS_REDI	=	parser/redirection/redirection_tools.c \
				parser/redirection/redirection_tools_two.c \
				parser/redirection/redirection_tools_three.c \
				parser/redirection/redirection_tools_four.c \
				parser/redirection/redirection.c \
				parser/redirection/here_doc.c \
				parser/redirection/here_doc_tools.c

SRCS_PARSE	=	parser/ft_split_parser.c parser/create_token_two.c \
				parser/create_token.c parser/error_check.c \
				parser/free.c parser/main.c parser/parse_actions.c \
				parser/parsing_tools.c parser/pipe_to_actions.c \
				parser/free_two.c parser/pipe_action_tools.c \
				parser/pipe_to_actions_tools.c

INCL	=	./includes/

NAME	= 	minishell

CC	=	cc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror #-g3 -fsanitize=address

SRCS	=	$(addprefix $(SRCS_PATH), $(SRCS_NAMES) $(SRCS_SIGNAL) $(SRCS_ENV) $(SRCS_BUILT) $(SRCS_EXEC) $(SRCS_REDI) $(SRCS_PARSE))

OBJS	=	${SRCS:.c=.o}

.c.o:
		@${CC} ${CFLAGS} -I$(INCL) -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@make --silent -C ./libft/
			${CC} ${CFLAGS} ${OBJS} libft/libft.a -I${INCL} -o ${NAME} -lreadline

all:		${NAME}

clean:
		${RM} ${OBJS}
		${RM} ${OBJS_BONUS}
		@make --silent -C ./libft clean

fclean:		clean
		@make --silent -C ./libft fclean
		${RM} ${NAME} ${NAME_BONUS}

re:		fclean all

bonus:	fclean all

.PHONY:
		all clean fclean re bonus
