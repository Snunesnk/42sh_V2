# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    21sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2020/02/04 13:46:37 by efischer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SOURCES_PATH := ./src/

SOURCES :=	main.c \
		debug.c \
		execute_job.c \
		job.c \
		redir.c \
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
		ft_putenv_table.c \
		execute_ast.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_exit.c \
		builtins/builtin_pwd.c \
		builtins/builtins_dispatcher.c \
		builtins/builtin_setenv.c \
		builtins/builtin_truefalse.c \
		builtins/builtin_type.c \
		builtins/builtin_unsetenv.c

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

PATH_LIB := ./libft/

INCLUDES := -I./src/ -I./src/builtins/ -I$(PATH_LIB)include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash --posix

TESTS_PATH := ./tools/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

TEST := $(SH) $(TESTS_PATH)$(TESTS_SCRIPT)

LDLIBS += $(PATH_LIB)libft.a

LDFLAGS += $(DEBUG)
#LDFLAGS += -flto=full

CFLAGS += -Wall -Wextra -Werror -D_POSIX_JOB_CONTROL -D_POSIX_C_SOURCE  $(DEBUG)
#CFLAGS += -fno-builtin -O2

DEBUG += -g -fsanitize=address
