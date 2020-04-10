/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/10 15:12:48 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

const struct s_tags	g_tags[] =
{
	{"${", &parameter_expansions, "}"},
	{"$", &dollar_expansions, ""},
	{"~", &tilde_expansion, ""},
	{"\0", NULL, NULL}
};

static int		expansion_dispatcher(char *str, int tilde)
{
	int		i;
	int		ref;
	char	*ptr;
	char	*closest;

	i = 0;
	closest = NULL;
	ref = -1;
	while (*(g_tags[i].opentag))
	{
		if (!tilde && !ft_strcmp("~", g_tags[i].opentag))
			break ;
		ptr = ft_strstr(str, g_tags[i].opentag);
		if (ptr && (!closest || (ptr < closest && closest)))
		{
			closest = ptr;
			ref = i;
		}
		++i;
	}
	return (ref);
}

static char		*get_closest_exp(char *str, int tilde)
{
	int		i;
	char	*ptr;
	char	*closest;

	i = 0;
	closest = NULL;
	while (*(g_tags[i].opentag))
	{
		if (!tilde && !ft_strcmp("~", g_tags[i].opentag))
			break ;
		ptr = ft_strstr(str, g_tags[i].opentag);
		if (ptr && (!closest || (ptr < closest && closest)))
			closest = ptr;
		++i;
	}
	return (closest);
}

static int		replace_expansion(char **token, char **next, int ref)
{
	size_t	lcontent;
	char	*new;
	size_t	lnew;
	size_t	lprefix;
	int		ret;

	lcontent = 0;
	ret = e_success;
	lprefix = (size_t)((*next) - (*token));
	if (!(ret = g_tags[ref].f(&lcontent, next,
	g_tags[ref].opentag, g_tags[ref].closetag)))
	{
		lnew = lprefix + ft_strlen(*next);
		new = (char*)ft_memalloc(sizeof(char) * (lnew + 1));
		ft_strncat(new, *token, lprefix);
		ft_memdel((void**)token);
		ft_strcat(new, *next);
		ft_memdel((void**)next);
		*next = &(new)[lcontent + lprefix];
		*token = new;
		return (e_success);
	}
	return (ret);
}

int				treat_single_exp(char **str, int tilde)
{
	int		ref;
	int		ret;
	char	*next;

	next = *str;
	while ((next = get_closest_exp(next, tilde)))
	{
		if (tilde && (next > *str
		|| (next == *str && (next[1] != '/' && next[1] != '\0'))))
		{
			tilde = 0;
			continue ;
		}
		ref = expansion_dispatcher(next, tilde);
		if ((ret = replace_expansion(str, &next, ref)))
		{
			psherror(ret, *str, e_cmd_type);
			return (ret);
		}
	}
	return (e_success);
}

int				treat_expansions(t_process *p)
{
	int	i;
	int	ret;

	i = 0;
	if (!p->argv || !*p->argv)
		return (e_invalid_input);
	while (i < p->argc)
	{
		ret = treat_single_exp(p->argv + i, 1);
		ret = !ret ? pathname_expansion(p, i) : ret;
		if (ret)
			return (ret);
		++i;
	}
	return (e_success);
}
