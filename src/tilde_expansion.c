/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/20 12:55:51 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pwd.h>

#include "libft.h"
#include "error.h"
#include "shell.h"

static int	replace_tilde(char **str, char *start, char *env)
{
	char	*cpy;

	if (!(cpy = ft_strjoin(env, start)))
		return (e_cannot_allocate_memory);
	*str = cpy;
	return (e_success);
}

static char	*get_end(char *str)
{
	char	*slash;
	char	*colon;

	if (!*str)
		return (str);
	slash = ft_strchr(str, '/');
	colon = ft_strchr(str, ':');
	if (slash && colon)
		return (slash < colon ? slash : colon);
	else if (slash)
		return (slash);
	else if (colon)
		return (colon);
	return (ft_strchr(str, 0));
}

static char	*get_dir(char *start, char *end)
{
	char *ptr;

	ptr = start + 1;
	while (ptr != end && *ptr == '0')
		++ptr;
	if (ptr == end)
	{
		if (*start == '-')
			return (get_shell_var("OLDPWD", g_env));
		else
			return (get_shell_var("PWD", g_env));
	}
	return (NULL);
}

static char	*get_home_value(char *start, char *end)
{
	struct passwd	*pwd;
	char			*home;

	if (start == end)
	{
		home = get_shell_var("HOME", g_env);
		if (home)
			return (home);
		pwd = getpwuid(getuid());
		if (pwd)
			home = pwd->pw_dir;
	}
	else
		home = get_user_home(start, end);
	return (home);
}

int			tilde_expansion(size_t *index, char **str, const char *opentag,
		const char *closetag)
{
	char	*env;
	char	*end;

	(void)opentag;
	(void)closetag;
	env = NULL;
	if (!*index)
	{
		end = get_end(*str + 1);
		if ((*str)[1] == '-' || (*str)[1] == '+' || (*str)[1] == '0')
			env = get_dir(*str + 1, end);
		if (!env && (*str)[1] != '+')
			env = get_home_value(*str + 1, end);
		if (env)
		{
			*index = ft_strlen(env);
			return (replace_tilde(str, end, env));
		}
	}
	*index = 1;
	return (replace_tilde(str, *str + 1, "~"));
}
