/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/09/25 21:25:10 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "shell.h"
#include "error.h"
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
	if (path_concat(&cpy) == e_success)
		return (cpy);
	else
	{
		ft_memdel((void**)&cpy);
		return (NULL);
	}
}

int				cmd_type(int argc, t_process *p)
{
	_Bool	error;
	int		i;
	char	*str;

	error = 0;
	i = 1;
	while (i < argc)
	{
		if (is_a_builtin(p->argv[i]))
			ft_dprintf(p->outfile, "%s is a shell builtin\n", p->argv[i]);
		else if (is_a_keyword(p->argv[i]))
			ft_dprintf(p->outfile, "%s is a shell keyword\n", p->argv[i]);
/*		else if ((str = gethash(p->argv[i])))
			ft_dprintf(p->outfile, "%s is hashed (%s)\n", p->argv[i], str);*/
/*		else if ((str = getalias(p->argv[i])))
			ft_dprintf(p->outfile, "%s is aliased to `%s'\n", p->argv[i], str);*/
		else if ((str = getbinpath(p->argv[i])))
		{
			ft_dprintf(p->outfile, "%s is %s\n", p->argv[i], str);
			ft_memdel((void**)&str);
		}
		else
		{
			error |= 1;
			ft_dprintf(p->errfile, "%s: %s: %s: not found\n", g_progname, *p->argv, p->argv[i]);
		}
		++i;
	}
	return (error);
}
