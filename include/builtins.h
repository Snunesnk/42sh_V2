/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:33:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 17:32:41 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

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
int				cmd_exit(int argc, char **argv);
int				cmd_env(int argc, char **argv);
int				cmd_pwd(int argc, char **argv);
int				cmd_cd(int argc, char **argv);

/*
** Functions in builtins_dispatcher.c
*/
int				builtins_dispatcher(char **argv);
typedef struct	s_builtins
{
	char	*key;
	int		(*f)(int, char**);
}				t_builtins;

_Bool				reserved_keyword(char *str);
struct	s_reserved_keyword
{
	char	*keyword;
};
#endif
