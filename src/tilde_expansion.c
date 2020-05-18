/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/12 16:23:06 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pwd.h>

#include "libft.h"
#include "error.h"
#include "shell.h"

static char	*get_home_value(void)
{
	struct passwd	*pwd;
	char			*home;

	home = get_shell_var("HOME", g_env);
	if (home)
		return (home);
	pwd = getpwuid(getuid());
	if (pwd)
		home = pwd->pw_dir;
	return (home);
}

static int	replace_tilde(char **str, char *start, char *env)
{
	char	*cpy;

	if (!(cpy = ft_strjoin(env, start)))
		return (e_cannot_allocate_memory);
	*str = cpy;
	return (e_success);
}

int			tilde_expansion(size_t *index, char **str, const char *opentag,
		const char *closetag)
{
	int	ret;
	char	*env;

	(void)opentag;
	(void)closetag;
	ret = e_success;
	if (!*index)
	{
		if ((*str)[1] == '-')
			env = get_shell_var("OLDPWD", g_env);
		else if ((*str)[1] == '+')
			env = get_shell_var("PWD", g_env);
		else
			env = get_home_value();
		env = !env ? "~" : env;
		*index = ft_strlen(env);
		ret = replace_tilde(str, (*str) + 1
			+ ((*str)[1] && ft_strchr("+-", (*str)[1])), env);
	}
	else
	{
		ret = replace_tilde(str, &(*str)[1], "~");
		*index = 1;
	}
	return (ret);
}
