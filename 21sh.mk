# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    21sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2020/03/12 17:52:05 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SOURCES_PATH := ./src/

SOURCES :=	main.c \
		ast.c \
		ast_order.c \
		build_redir.c \
		debug.c \
		debug_ast.c \
		del.c \
		do_redir.c \
		do_redir2.c \
		do_redir3.c \
		error.c \
		execute_ast.c \
		execute_ast2.c \
		execute_job.c \
		execute_job2.c \
		execute_process.c \
		expansions.c \
		expansion_utils.c \
		export_utils.c \
		ft_merge_sort.c \
		ft_putenv_table.c \
		get_env_list.c \
		get_env_tab.c \
		get_next_token.c \
		get_param.c \
		get_token_word.c \
		hash_table.c \
		hash_table_utils.c \
		init_shell.c \
		init_enum_tab.c \
		job.c \
		job_control.c \
		job_control2.c \
		job_control3.c \
		job_bookeeping.c \
		launch_builtin.c \
		launch_lexer_parser.c \
		lexer.c \
		lexer_utils.c \
		manage_shell_var.c \
		new_node_ast.c \
		only_assignments.c \
		dollar_expansions.c \
		parameter_expansions.c \
		parser.c \
		path.c \
		path_concat.c \
		pathname_expansion.c \
		process.c \
		redir.c \
		redir_less.c \
		redir_great.c \
		redir_great2.c \
		signals.c \
		tilde_expansion.c \
		treat_shell_variables.c \
		undo_redir.c \
		undo_redir2.c \
		undo_redir3.c \
		utils_job.c \
		builtins/builtin_fg.c \
		builtins/builtin_fc.c \
		builtins/builtin_fc_list_edit.c \
		builtins/builtin_fc_s_opt.c \
		builtins/builtin_fc_utils.c \
		builtins/builtin_fc_hist_num.c \
		builtins/builtin_bg.c \
		builtins/builtin_jobs.c \
		builtins/builtin_cd.c \
		builtins/builtin_cd_path.c \
		builtins/builtin_cd_operand.c \
		builtins/builtin_echo.c \
		builtins/builtin_exit.c \
		builtins/builtins_dispatcher.c \
		builtins/builtin_setenv.c \
		builtins/builtin_truefalse.c \
		builtins/builtin_type.c \
		builtins/builtin_hash.c \
		builtins/builtin_hash_print.c \
		builtins/builtin_hash_utils.c \
		builtins/builtin_unsetenv.c \
		builtins/builtin_export.c \
		builtins/builtin_set.c \
		builtins/builtin_unset.c \
		builtins/builtin_alias.c \
		builtins/builtin_unalias.c \
		../globbings/ft_fnmatch/char_class_functions_1.c \
		../globbings/ft_fnmatch/char_class_functions_2.c \
		../globbings/ft_fnmatch/char_class_functions_3.c \
		../globbings/ft_fnmatch/ft_fnmatch.c \
		../globbings/ft_fnmatch/g_char_classes.c \
		../globbings/ft_fnmatch/match_brack.c \
		../globbings/ft_fnmatch/match.c \
		../globbings/ft_glob/build_brace_patterns.c \
		../globbings/ft_glob/build_patterns.c \
		../globbings/ft_glob/file_utils.c \
		../globbings/ft_glob/ft_glob.c \
		../globbings/ft_glob/ft_glob_internal.c \
		../globbings/ft_glob/match_patterns.c \
		../globbings/ft_glob/slash_path.c \
		../globbings/ft_glob/store_match_list.c \
		../globbings/utils/ft_lst_at.c \
		../globbings/utils/ft_lst_merge.c \
		../globbings/utils/ft_lst_pop.c \
		../globbings/utils/ft_lst_quicksort.c \
		../globbings/utils/ft_lst_size.c \
		../globbings/utils/ft_swap_p.c \
		../readline/bind.c \
		../readline/display.c \
		../readline/emacs_keymap.c \
		../readline/vim_keymap.c \
		../readline/vim.c \
		../readline/history.c \
		../readline/history_expand.c \
		../readline/history_lookup.c \
		../readline/history_utils.c \
		../readline/autocomplete.c \
		../readline/insert_compl.c \
		../readline/fill_data_util.c \
		../readline/command_complete.c \
		../readline/file_complete.c \
		../readline/print_cmpl_tree.c \
		../readline/fill_data.c \
		../readline/avl_fill.c \
		../readline/avl_utils.c \
		../readline/avl_sort.c \
		../readline/init.c \
		../readline/input.c \
		../readline/quotes.c \
		../readline/readline.c \
		../readline/signals.c \
		../readline/terminal.c \
		../readline/text.c \
		../readline/text2.c \
		../readline/text3.c \
		../readline/text4.c \
		../readline/text5.c \
		../readline/text6.c \
		../readline/text7.c \
		../readline/text_hist.c \
		../readline/tty.c \
		../readline/utils.c \
		../readline/utils_suite2.c \
		../readline/utils_suite.c

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

PATH_LIB := ./libft/

INCLUDES := -I./includes/ -I./src/builtins/ -I$(PATH_LIB)include/ -I./readline/ -I./globbings/includes

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash --posix

TESTS_PATH := ./tools/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

TEST := $(SH) $(TESTS_PATH)$(TESTS_SCRIPT)

LDLIBS += $(PATH_LIB)libft.a -lncurses

LDFLAGS += $(DEBUG)
#LDFLAGS += -flto=full

CFLAGS += -Wall -Wextra -Werror -D_POSIX_JOB_CONTROL -D_POSIX_C_SOURCE=200809L $(DEBUG)
#CFLAGS += -fno-builtin -O2

DEBUG += -g3 -fsanitize=address,undefined
