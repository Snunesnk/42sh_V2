# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    42sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2020/08/09 11:27:00 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SOURCES_PATH := ./src/

SOURCES :=	main.c \
		main_error.c \
		ast.c \
		graph.c \
		ast_utils.c \
		build_redir.c \
		check_alias.c \
		debug.c \
		del.c \
		do_redir.c \
		do_redir2.c \
		do_redir3.c \
		error.c \
		input.c \
		get_input_fd.c \
		execute_ast.c \
		execute_ast2.c \
		execute_job.c \
		execute_job2.c \
		execute_job3.c \
		execute_process.c \
		treat_expansions.c \
		treat_single_exp.c \
		expansion_utils.c \
		subshell_utils.c \
		ft_merge_sort.c \
		ft_putenv_table.c \
		get_env_list.c \
		get_env_tab.c \
		get_next_token.c \
		get_param.c \
		hash_table.c \
		hash_table_utils.c \
		init_shell.c \
		is_valid_redir.c \
		parse_table.c \
		job.c \
		job_utils.c \
		job_utils2.c \
		job_control.c \
		job_control2.c \
		job_control3.c \
		job_bookeeping.c \
		launch_builtin.c \
		lexer.c \
		lexer_utils.c \
		manage_shell_var.c \
		assignments.c \
		dollar_expansions.c \
		parameter_expansions.c \
		parser.c \
		subprompt.c \
		path_concat.c \
		pathname_expansion.c \
		process.c \
		quotes.c \
		redir.c \
		redir_utils.c \
		redir_less.c \
		redir_great.c \
		redir_great2.c \
		set_shell_var.c \
		signals.c \
		tilde_expansion.c \
		treat_shell_variables.c \
		undo_redir.c \
		undo_redir2.c \
		load_config.c \
		field_split.c \
		heredoc.c \
		expand_heredoc.c \
		get_str_qmode.c \
		userpwd.c \
		builtins/builtin_fg.c \
		builtins/builtin_fc.c \
		builtins/builtin_fc_list_edit.c \
		builtins/builtin_fc_s_opt.c \
		builtins/builtin_fc_utils.c \
		builtins/builtin_fc_hist_num.c \
		builtins/builtin_bg.c \
		builtins/builtin_jobs.c \
		builtins/builtin_cd.c \
		builtins/builtin_cd_concat.c \
		builtins/builtin_cd_access.c \
		builtins/builtin_echo.c \
		builtins/builtin_exit.c \
		builtins/builtins_dispatcher.c \
		builtins/builtin_truefalse.c \
		builtins/builtin_type.c \
		builtins/builtin_hash.c \
		builtins/builtin_hash_print.c \
		builtins/builtin_hash_utils.c \
		builtins/builtin_export.c \
		builtins/builtin_set.c \
		builtins/builtin_set_utils.c \
		builtins/builtin_unset.c \
		builtins/builtin_alias.c \
		builtins/builtin_unalias.c \
		builtins/builtin_builtin.c \
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
		../readline/bind.c \
		../readline/display.c \
		../readline/display_utils.c \
		../readline/place_cursor.c \
		../readline/get_prompt.c \
		../readline/emacs_keymap.c \
		../readline/vim_keymap.c \
		../readline/vim.c \
		../readline/vim2.c \
		../readline/vim3.c \
		../readline/vim4.c \
		../readline/vim5.c \
		../readline/vim6.c \
		../readline/vim7.c \
		../readline/vim8.c \
		../readline/vim9.c \
		../readline/get_vim_cmd_count.c \
		../readline/history.c \
		../readline/history_expand.c \
		../readline/history_expand_utils.c \
		../readline/history_lookup.c \
		../readline/history_utils.c \
		../readline/autocomplete.c \
		../readline/hist_complete.c \
		../readline/autocomplete_utils.c \
		../readline/autocompl_color.c \
		../readline/insert_compl.c \
		../readline/fill_data_util.c \
		../readline/command_complete.c \
		../readline/cd_complete.c \
		../readline/file_complete.c \
		../readline/var_complete.c \
		../readline/print_cmpl_tree.c \
		../readline/prepare_printing.c \
		../readline/fill_data.c \
		../readline/get_compl_range.c \
		../readline/avl_fill.c \
		../readline/avl_utils.c \
		../readline/avl_sort.c \
		../readline/init.c \
		../readline/input.c \
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
		../readline/utils_suite.c \
		../readline/highlight.c

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

PATH_LIB := ./libft/

INCLUDES := -I./includes/ -I./src/builtins/ -I$(PATH_LIB)include/ -I./readline/ -I./globbings/includes

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

SH := bash --posix

TESTS_PATH := ./tools/

TESTS_SCRIPT := launch_test.sh "launch from makefile"

TEST := $(SH) $(TESTS_PATH)$(TESTS_SCRIPT)

LDLIBS += $(PATH_LIB)libft.a -ltermcap

LDFLAGS += $(DEBUG)

CFLAGS += -Wall -Wextra -Werror -g3 -D_POSIX_JOB_CONTROL -D_POSIX_C_SOURCE=200809L $(DEBUG)
DEBUG += -fsanitize=address,undefined
CFLAGS += -fno-builtin -O2
