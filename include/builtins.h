/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:33:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/18 10:29:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

/*
** Utils for builtins
*/
int				ft_putenv_table(char ***env, const char *name,
				const char *value, int overwrite);
int				is_a_builtin(char *cmd);

/*
** Functions in builtins.c
*/
int				cmd_unsetenv(int argc, t_process *p);
int				cmd_setenv(int argc, t_process *p);
int				cmd_echo(int agrc, t_process *p);
int				cmd_type(int agrc, t_process *p);
int				cmd_exit(int argc, t_process *p);
int				cmd_true(int argc, t_process *p);
int				cmd_false(int argc, t_process *p);
int				cmd_env(int argc, t_process *p);
int				cmd_pwd(int argc, t_process *p);
int				cmd_cd(int argc, t_process *p);
int				cmd_set(int argc, t_process *p);
int				cmd_fg(int argc, t_process *p);

/*
** Functions in builtins_dispatcher.c
*/
int				builtins_dispatcher(t_process *p);
typedef struct	s_builtins
{
	const char *const	key;
	int		(*const f)(int, t_process *p);
}				t_builtins;

_Bool				prior_builtin(char *str);
struct	s_prior_builtin
{
	const char *const	pbuiltin;
};

extern const t_builtins	g_builtins[];

struct	s_keywords
{
	const char *const	keyword;
};

#endif
