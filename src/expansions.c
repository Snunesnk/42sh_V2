/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/15 10:15:47 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "quotes.h"

const struct s_tags	g_tags[] =
{
	{"${", &parameter_expansions, "}"},
	{"$", &dollar_expansions, ""},
	{"~", &tilde_expansion, ""},
	{"\0", NULL, NULL}
};

static char	*get_closest_exp(char *str, int tilde, int *ref, int *qmode)
{
	int		i;
	char	*ptr;
	char	*closest;
	int		tmp_qmode;
	int		orig_qmode;

	i = 0;
	*ref = -1;
	closest = NULL;
	orig_qmode = *qmode;
	while (*(g_tags[i].opentag))
	{
		tmp_qmode = orig_qmode;
		if (!tilde && !ft_strcmp("~", g_tags[i].opentag))
			break ;
		ptr = ft_strstr_qmode(str, g_tags[i].opentag, DQUOTE, &tmp_qmode);
		if (ptr && (!closest || ptr < closest))
		{
			*qmode = tmp_qmode;
			closest = ptr;
			*ref = i;
		}
		++i;
	}
	return (closest);
}

static int	replace_expansion(char **token, char **next, int ref)
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

int			treat_single_exp(char **str, int tilde)
{
	int		ref;
	int		ret;
	int		qmode;
	char	*next;

	next = *str;
	qmode = NO_QUOTE;
	while ((next = get_closest_exp(next, tilde, &ref, &qmode)))
	{
		if (tilde && (next > *str || (next[1] && next[1] != '/')))
			tilde = 0;
		if (!tilde && *next == '~')
			continue ;
		if ((ret = replace_expansion(str, &next, ref)))
		{
			psherror(ret, *str, e_cmd_type);
			return (ret);
		}
	}
	return (e_success);
}

int			treat_expansions(t_process *p)
{
	int	i;
	int	ret;
	int	skip;

	i = 0;
	if (!p->argv || !*p->argv)
		return (e_invalid_input);
	while (i < p->argc)
	{
		skip = 0;
		ret = treat_single_exp(p->argv + i, 1)
			|| pathname_expansion(p, i, &skip);
		if (ret)
			return (ret);
		else if (!skip)
			ret = rm_quotes(p->argv + i, NO_QUOTE);
		i += skip ? skip : 1;
	}
	trim_argv(p);
	return (e_success);
}
