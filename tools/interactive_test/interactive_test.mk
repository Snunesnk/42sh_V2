# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    interactive_test.mk                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2020/06/10 23:15:49 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = interactive_test

SOURCES_PATH := ./src/

SOURCES :=	main.c \
			get_process_info.c \
			send_input.c \
			utils.c \
			wait.c

CC = clang

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

INCLUDES := -I./include/

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

CFLAGS += -Wall -Wextra -Werror -g3 -fsanitize=undefined,address
