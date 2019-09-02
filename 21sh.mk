# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    21sh.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/08/21 12:47:24 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SOURCES_PATH := ./src/

SOURCES :=	main.c \
			transv/error.c \
			transv/signals.c \
			input/path.c \
			input/prompt.c \
			input/input.c \
			lex/lexer.c \
			lex/expansions/expansions.c \
			lex/expansions/expansion_utils.c \
			lex/expansions/get_param.c \
			lex/expansions/parameter_expansions.c \
			lex/expansions/tilde_expansion.c \
			lex/separators/unglue_sep.c \
			synt/synt.c \
			synt/synt_const.c \
			jcont/jcont.c \
			job/job.c \
			job/path_concat.c \
			job/builtins/builtin_cd.c \
			job/builtins/builtin_echo.c \
			job/builtins/builtin_env.c \
			job/builtins/builtin_exit.c \
			job/builtins/builtin_pwd.c \
			job/builtins/builtin_setenv.c \
			job/builtins/builtin_unsetenv.c \
			job/builtins/builtins_dispatcher.c \
			job/builtins/ft_putenv_table.c \

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

INCLUDES := -I./include/ -I./libft/include/

PATH_LIB = ./libft/

LIB = $(PATH_LIB)libft.a

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash

TESTS_PATH := ./tools/tests/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

CFLAGS += -fno-builtin -O2 -flto=full
#CFLAGS += -g -fsanitize=address
