# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    21sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/12/18 12:48:20 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SOURCES_PATH := ./src/

SOURCES :=	main.c \
		debug.c \
		execute_jobs.c \
		job.c \
		process.c \
		launch_builtin.c \
		path_concat.c \
		utils_job.c \
		lexer.c \
		get_next_token.c \
		ast_order.c \
		debug_ast.c \
		parser.c \
		init_shell.c \
		path.c \
		input.c \
		error.c \
		builtin_cd.c \
		builtin_echo.c \
		builtin_env.c \
		builtin_exit.c \
		builtin_pwd.c \
		builtins_dispatcher.c \
		builtin_setenv.c \
		builtin_truefalse.c \
		builtin_type.c \
		builtin_fg.c \
		builtin_unsetenv.c \
		ft_putenv_table.c

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

PATH_LIB := ./libft/

INCLUDES := -I./include/ -I$(PATH_LIB)include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash --posix

TESTS_PATH := ./tools/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

TEST := $(SH) $(TESTS_PATH)$(TESTS_SCRIPT)

LDLIBS += $(PATH_LIB)libft.a

LDFLAGS += $(DEBUG)
#LDFLAGS += -flto=full

CFLAGS += -Wall -Wextra -Werror -D_POSIX_JOB_CONTROL -D_POSIX_C_SOURCE -std=c99 -ansi $(DEBUG)
#CFLAGS += -fno-builtin -O2

DEBUG += -g -fsanitize=address
