/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:33:04 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/12 10:00:18 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

# define HASH_D_OPTION 1
# define HASH_L_OPTION 2
# define HASH_P_OPTION 4
# define HASH_R_OPTION 8
# define HASH_T_OPTION 16
# define FNV_OFFSET 2166136261
# define FNV_PRIME 16777619

struct			s_cd
{
	struct stat		buf;
	char			*path;
	char			*oldpwd;
	char			*tmp;
	int				ret;
	_Bool			p;
};

typedef struct	s_builtins
{
	const char *const	key;
	int					(*const f)(int, char**);
}				t_builtins;

extern const t_builtins	g_builtins[];

struct			s_keywords
{
	const char *const	keyword;
};

int				ft_putenv_table(char ***env, const char *name,
		const char *value, int overwrite);
int				is_a_builtin(char *cmd);
int				cmd_unsetenv(int argc, char **argv);
int				cmd_setenv(int argc, char **argv);
int				cmd_echo(int agrc, char **argv);
int				cmd_type(int agrc, char **argv);
int				cmd_exit(int argc, char **argv);
int				cmd_true(int argc, char **argv);
int				cmd_false(int argc, char **argv);
int				cmd_cd(int argc, char **argv);
int				cmd_set(int argc, char **argv);
int				cmd_fg(int argc, char **argv);
int				cmd_bg(int argc, char **argv);
int				cmd_jobs(int argc, char **argv);
int				cmd_hash(int argc, char **argv);
int				cmd_export(int argc, char **argv);
int				cmd_unset(int argc, char **argv);
char			get_next_opt(char ***argv);
int				check_for_needed_arguments(int options_list, char **argv);
int				exec_hash_builtin(int options_list, char **argv);
int				print_hashed_commands(int options_list);
void			del_hashed_commands(void);
int				print_hashed_targets(int options_list, char **argv);
int				change_hash_entry(char *pathname, char *name);
void			remove_hash_entry(char *name);
int				print_error(int error_no, char *message, int ret);
void			print_hashed_targets_util(t_hash_table *tmp, int l_option,
		char *arg, int multiple);
void			print_hashed_commands_util(t_hash_table *tmp, int l_option);
char			deal_with_p_opt(char ***args, int *x);
char			return_next_opt(char ***args, int *x);
int				builtins_dispatcher(char **argv);
int				concatenable_operand_while(const char *str);
int				concatenable_operand(const char *str);
int				gfp_env(struct s_cd *cd);
int				gfp_previous(char **argv, struct s_cd *cd);
int				gfp_concatenable(char **argv, struct s_cd *cd);
int				set_oldpwd(void);
int				refresh_pwd(const char *path, _Bool p);
int				cdpath_concat(char **path, char *env);
int				getfullpath(char **argv, struct s_cd *cd);
int				stat_failure(char **argv, struct s_cd *cd);

extern char	*g_pathname;

#endif
