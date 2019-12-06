# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    21sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/10/16 19:18:42 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SOURCES_PATH := ./src/

SOURCES :=	main.c \
		input/input.c \
		input/path.c \
		input/prompt.c \
		lexer/lexer.c \
		lexer/grammar_symbols.c \
		parser/parser.c \
		parser/job.c \
		parser/path_concat.c \
		modules/error.c \
		modules/signals.c \
		modules/builtins/builtin_cd.c \
		modules/builtins/builtin_echo.c \
		modules/builtins/builtin_env.c \
		modules/builtins/builtin_exit.c \
		modules/builtins/builtin_pwd.c \
		modules/builtins/builtins_dispatcher.c \
		modules/builtins/builtin_set.c \
		modules/builtins/builtin_setenv.c \
		modules/builtins/builtin_truefalse.c \
		modules/builtins/builtin_type.c \
		modules/builtins/builtin_unsetenv.c \
		modules/builtins/ft_putenv_table.c \
		modules/builtins/shell_variables/alloc_shell_variables.c \
		modules/builtins/shell_variables/free_shell_variables.c \
		modules/builtins/shell_variables/init_shell_variables.c \
		modules/builtins/shell_variables/shell_variables.c \
		modules/builtins/shell_variables/utils_shell_variables.c \
		modules/expansions/expansions.c \
		modules/expansions/expansion_utils.c \
		modules/expansions/get_param.c \
		modules/expansions/parameter_expansions.c \
		modules/expansions/tilde_expansion.c

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
