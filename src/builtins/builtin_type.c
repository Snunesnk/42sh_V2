/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/21 13:59:00 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

static const struct s_keywords	g_keywords[] =
{
	{ "{" },
	{ "}" },
	{ "!" },
	{ "do" },
	{ "if" },
	{ "fi" },
	{ "for" },
	{ "case" },
	{ "esac" },
	{ "then" },
	{ "else" },
	{ "done" },
	{ "until" },
	{ "while" },
	{ "select" },
	{ "function" },
	{ NULL }
};

static _Bool	is_a_keyword(char *word)
{
	int	i;

	i = 0;
	while (g_keywords[i].keyword)
	{
		if (!ft_strcmp(g_keywords[i].keyword, word))
			return (1);
		else
			++i;
	}
	return (0);
}

static char		*getbinpath(char *bin)
{
	char	*cpy;

	if (!(cpy = ft_strdup(bin)))
		return (NULL);
	if (path_concat(&cpy, NULL, NULL, NULL) == e_success)
	{
		if (cpy && *cpy != '/')
			cpy = fullpath_concat(cpy);
		if (access(cpy, X_OK))
		{
			ft_memdel((void**)&cpy);
			return (NULL);
		}
		return (cpy);
	}
	else
	{
		ft_memdel((void**)&cpy);
		return (NULL);
	}
}

static void		display_err_msg(_Bool *error, char *name)
{
	*error |= 1;
	pbierror("%s: not found", name);
}

static void		tests_suite(char **argv, _Bool *error, char *str)
{
	if ((str = getbinpath(*argv)))
	{
		ft_printf("%s is %s\n", *argv, str);
		ft_memdel((void**)&str);
	}
	else
		display_err_msg(error, *argv);
}

int				cmd_type(int argc, char **argv)
{
	_Bool			error;
	t_hash_table	*path;
	char			*str;

	(void)argc;
	error = 0;
	while (*++argv)
	{
		if (!access(*argv, X_OK) && ft_strstr(*argv, "/"))
			ft_printf("%s is %s\n", *argv, *argv);
		else if ((str = get_shell_var(*argv, g_alias)))
			ft_printf("%s is aliased to `%s'\n", *argv, str);
		else if (is_a_builtin(*argv))
			ft_printf("%s is a shell builtin\n", *argv);
		else if (is_a_keyword(*argv))
			ft_printf("%s is a shell keyword\n", *argv);
		else if ((path = find_occurence(*argv)))
			ft_printf("%s is hashed (%s)\n", *argv, path->command_path);
		else
			tests_suite(argv, &error, str);
	}
	return (error);
}
