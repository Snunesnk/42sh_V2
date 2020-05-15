/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/15 10:20:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

int			is_a_valid_chr(const char c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_'))
		return (1);
	else
		return (0);
}

int			is_valid_param(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_a_valid_chr(str[i]))
			return (e_bad_substitution);
		++i;
	}
	return (e_success);
}

size_t		ft_varlen(const char *s, const char *closetag)
{
	size_t	len;
	char	*end;

	len = 0;
	if (*s && !*closetag)
	{
		while (s[len] && is_a_valid_chr(s[len]))
			++len;
		if (s[len] == '?' && len == 0)
			++len;
	}
	else if (*s && *closetag)
	{
		end = ft_strstr(s, closetag);
		if (!end)
			return (len);
		len = (size_t)(end - s);
	}
	return (len);
}

static int	count_argc(t_process *p)
{
	int	argc;
	int	i;

	i = 0;
	argc = 0;
	while (i < p->argc)
	{
		if (p->argv[i][0])
			++argc;
		++i;
	}
	return (argc);
}

void		trim_argv(t_process *p)
{
	char	**argv;
	int		argc;
	int		i;

	i = 0;
	argc = count_argc(p);
	argv = ft_memalloc(sizeof(char*) * (argc + 1));
	argc = 0;
	while (i < p->argc)
	{
		if (p->argv[i][0])
		{
			argv[argc] = p->argv[i];
			++argc;
		}
		else
			ft_memdel((void**)&p->argv[i]);
		++i;
	}
	ft_memdel((void**)&p->argv);
	p->argv = argv;
	p->argc = argc;
}
