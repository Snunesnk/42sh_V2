/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:33:04 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/11 20:38:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "shell.h"

/*
** Flags for hash options
*/
# define HASH_D_OPTION 1
# define HASH_L_OPTION 2
# define HASH_P_OPTION 4
# define HASH_R_OPTION 8
# define HASH_T_OPTION 16

/*
** Flags for fc options, 2 is used to check if an error occured
*/
# define FC_N_OPTION 1
# define FC_L_OPTION 4
# define FC_R_OPTION 8
# define FC_S_OPTION 16
# define FC_E_OPTION 32

/*
** Values used to hash strings
*/
#define FNV_OFFSET 2166136261
#define FNV_PRIME 16777619

/*
** Utils for builtins
*/
int				ft_putenv_table(char ***env, const char *name,
				const char *value, int overwrite);
int				is_a_builtin(char *cmd);

/*
** Functions in builtins.c
*/
int				cmd_unsetenv(int argc, char **argv);
int				cmd_setenv(int argc, char **argv);
int				cmd_echo(int agrc, char **argv);
int				cmd_type(int agrc, char **argv);
int				cmd_exit(int argc, char **argv);
int				cmd_true(int argc, char **argv);
int				cmd_false(int argc, char **argv);
int				cmd_pwd(int argc, char **argv);
int				cmd_cd(int argc, char **argv);
int				cmd_set(int argc, char **argv);
int				cmd_fg(int argc, char **argv);
int				cmd_fc(int argc, char **argv);
int				cmd_bg(int argc, char **argv);
int				cmd_jobs(int argc, char **argv);
int				cmd_hash(int argc, char **argv);
int				cmd_export(int argc, char **argv);
int				cmd_unset(int argc, char **argv);

/*
** Hash functions
*/
char			get_next_opt(char ***argv, const char *options_list);
int				check_for_needed_arguments(int options_list, char **argv);
int				exec_hash_builtin(int options_list, char **argv);
int				print_hashed_commands(int options_list);
void			del_hashed_commands(void);
int				print_hashed_targets(int options_list, char **argv);
int				change_hash_entry(char *pathname, char *name);
void			remove_hash_entry(char *name);
int				print_usage(char *args);
void			print_hashed_targets_util(t_hash_table *tmp, int l_option, \
		char *arg, int multiple);
void			print_hashed_commands_util(t_hash_table *tmp, int l_option);
char			deal_with_spe_opt(char ***args, int *x);
char			return_next_opt(char ***args, int *x, const char *options_list);

/*
** Substitution struc for fc
*/
typedef struct	s_sub
{
	struct s_sub	*next;
	struct s_sub	*prev;
	char			*pat;
	char			*rep;
}				t_sub;

/*
** Fc functions
*/
int				exec_fc_other_opt(int opt_list, char **args);
char			*ft_strreplace(char **str, char *pattern, char *replacement);
void			fc_replace_last_hist(char *tmp);
void			free_substitute(t_sub *substitute);
void			get_hist_num(char **args, int *opt_list, int *hist_end, \
		int *hist_beg);
int				fc_invalid_input(char *args);
void			print_error(char *usage, char option, int mode);
int				exec_fc_s_opt(char **args);
void			swap_entries(int *hist_end, int *hist_beg);

/*
** Global var util for get_next_opt
*/
extern char	*g_needed_arg;
extern char	*g_builtin_name;

/*
** Functions in builtins_dispatcher.c
*/
int				builtins_dispatcher(char **argv);
typedef struct	s_builtins
{
	const char *const	key;
	int			(*const f)(int, char**);
}				t_builtins;

extern const t_builtins	g_builtins[];

struct	s_keywords
{
	const char *const	keyword;
};

#endif
