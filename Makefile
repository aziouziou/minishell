# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 10:17:01 by abouazi           #+#    #+#              #
#    Updated: 2023/04/29 22:25:09 by abziouzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Compilation - Files & Directories

NAME				=	minishell

CC					=	cc

CCFLAGS				=	-Wall -Wextra -Werror -g

READLINE			=	$(shell brew --prefix readline)

INCLUDE_READLINE	=	$(addprefix $(READLINE),/include)

LIB_READLINE		=	$(addprefix $(READLINE),/lib)

RM					=	rm -rf

MS_BUILTIN			=	$(addprefix ms_builtin/, ms_builtin ms_builtin_env ms_cd	\
							ms_echo ms_exit ms_export ms_export_ext ms_export_utils ms_pwd)

MS_ENV				=	$(addprefix ms_env/, ms_env ms_expander)

MS_EXECUTOR			=	$(addprefix ms_executor/, ms_executor ms_executor_ext	\
							ms_executor_ext_2 ms_executor_utils ms_heredoc		\
							ms_heredoc_ext ms_pipe)

MS_LEXER			=	$(addprefix ms_lexer/, ms_lexer ms_lexer_ext ms_lexer_utils	\
							ms_syntax ms_tokens_utils)

MS_LIBFT			=	$(addprefix ms_libft/, ms_atoi ms_isalnum ms_isalpha		\
							ms_isdigit ms_isspace ms_is_white_space ms_itoa	\
							ms_memcpy ms_putstr_fd ms_split ms_strchr 		\
							ms_strcmp ms_strdup ms_strjoin ms_strlcpy		\
							ms_strlen ms_strndup ms_strnstr ms_strstr		\
							ms_strtrim ms_substr)

MS_PARSER			=	$(addprefix ms_parser/, ms_parser ms_parser_utils ms_redir	\
							ms_redir_utils)

MS_UTILS			=	$(addprefix ms_utils/,  ms_error ms_garbage ms_launch		\
							ms_readline ms_signals)

MS_FILES			=	$(addprefix src/, ms_main $(MS_UTILS) $(MS_LIBFT) $(MS_LEXER)\
							$(MS_ENV) $(MS_PARSER) $(MS_EXECUTOR) $(MS_BUILTIN))

HEADER				=	$(addprefix inc/, minishell.h ms_libft.h)

INC					=	-I inc

SRC					=	$(MS_FILES:=.c)
OBJ					=	$(MS_FILES:=.o)

#	Commands

.PHONY				:	all clean fclean re

all					:	$(NAME)

%.o					:	%.c $(HEADER)
						@ $(CC) $(CCFLAGS) -I $(INCLUDE_READLINE)  -c $< -o $@

$(NAME)				:	$(OBJ) $(HEADER)
						@ $(CC) $(CCFLAGS) -I $(INCLUDE_READLINE) -L $(LIB_READLINE) -lreadline  $(OBJ) $(INC) -o $(NAME)

clean				:
						@ $(RM) $(OBJ)

fclean				:	clean
						@ $(RM) $(NAME)

re					:	fclean all
