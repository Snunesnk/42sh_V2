/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/21 08:22:22 by yforeau          ###   ########.fr       */
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
	char *cpy;

	if (!(cpy = ft_strdup(bin)))
		return (NULL);
	if (path_concat(&cpy, NULL, NULL, NULL) == e_success)
		return (cpy);
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

int				cmd_type(int argc, char **argv)
{
	_Bool			error;
	t_hash_table	*path;
	char			*str;

	(void)argc;
	error = 0;
	while (*++argv)
	{
		if ((str = get_shell_var(*argv, g_alias)))
			ft_printf("%s is aliased to `%s'\n", *argv, str);
		else if (is_a_builtin(*argv))
			ft_printf("%s is a shell builtin\n", *argv);
		else if (is_a_keyword(*argv))
			ft_printf("%s is a shell keyword\n", *argv);
		else if ((path = find_occurence(*argv)))
			ft_printf("%s is hashed (%s)\n", *argv, path->command_path);
		else if ((str = getbinpath(*argv)))
		{
			ft_printf("%s is %s\n", *argv, str);
			ft_memdel((void**)&str);
		}
		else
			display_err_msg(&error, *argv);
	}
	return (error);
}
